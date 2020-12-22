/**
 *
 * 首先，想到点分治然后发现点分治不行，是对的
 * 这种时候，就要使用核心思想是轻重链的树上启发式合并
 *
 * 关于 DSU 的记录：
 * - 如果采用暴力做法（set/vector）每一个点都需要遍历记录的所有的点，是 n 同阶的
 * - 采取拆位的做法：将这个数字集的每一位是 1/0 的个数统计好并记录
 * - 想要得到一个数字分别和整个数集中的数字的异或和，相当于将每一位分别和这些位异或
 * - 每一位有根据运算法则满足的位的个数个 1，它们被累加了起来
 * - 所以，这个时候将二进制看作还没有进位的数字，乘以当前位的权重并累加即可
 * - 虽然这种二进制拆位仅被应用于异或和，但是异或问题尽量考虑拆位分别记录/考虑
 * 虽然最终暴力使用 vector 存储没有被卡掉，但这才是这个题目的正解
 * 
 * DSU on tree 的 统计子树间贡献 的例题；还考察了二进制异或拆位
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#endif

template <class printable>
void trace(const char *name, printable &&value)
{cerr << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    cerr.write(names, separate - names) << " = " << value << ',';
    trace(separate + 1, list...);
}

template <class T>
void print(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
void print(char ch) {putchar(ch);}
template <class T, class ...Ts>
void print(T x, Ts ...xs) {print(x), print(xs...);}
void println() {puts("");}
template <class T>
void println(T x)
{print(x), putchar('\n');}

static class Scanner
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

    static inline bool isBlank(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
    template <class T, class... Ts>
    void operator()(T &&x, Ts &&... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

const int N = 1e5 + 5, M = N;
const int inf = 0x3f3f3f3f;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N], deg[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(deg, 0, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
        ++ deg[v], ++ deg[u];
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }
}

uint a[N];
longs ans = 0;

namespace DSUonTree
{
    const auto bit = 20u;
    int siz[N], very[N];
    uint ds[(1u << bit) + 5][bit][2];
    vector<int> temp;
    bitset<(1u << bit) + 5> appear;

    using namespace FWS;

    void preDFS(int u, int fa)  // 预处理：统计子树大小，找到重儿子并记录
    {
        siz[u] = 1, very[u] = 0;
        forEach(u, [&](const edge &e)
        {
            if (e.v == fa) return;
            preDFS(e.v, u), siz[e.v];
            if (!very[u] || siz[e.v] > siz[very[u]])
                very[u] = e.v;
            siz[u] += siz[e.v];
        });
    }

    void calc(uint u, int fa, int lca)  // 子树间的统计：用记录的已考虑的点的信息更新答案
    {
        temp.push_back(u);      // 当前子树统计完了之后需要加入记录的节点列表（当前子树全部节点
        for (auto i = 0u; i < bit; ++ i)
            ans += (1ull << i) * ds[a[u] ^ a[lca]][i][!(1u & (u >> i))];
        forEach(u, [&](const edge &e)
        {
            if (e.v == fa) return;
            calc(e.v, u, lca);
        });
    }

    void clear(int u, int fa)   // 递归清除当前子树所有的节点为记录增加的信息
    {
        if (appear[a[u]])
        {
            memset(ds[a[u]], 0, sizeof(ds[a[u]]));
            appear[a[u]] = false;
        }
        forEach(u, [&](const edge &e)
        {
            if (e.v == fa) return;
            clear(e.v, u);
        });
    }

    void insert(uint u)     // 求子树间贡献使用，插入已经处理完的子树的节点信息
    {
        for (auto i = 0u; i < bit; ++ i)
            ++ ds[a[u]][i][(u >> i) & 1u];
        appear[a[u]] = true;
    }

    void dfs(int u, int fa, bool keep)
    {
        forEach(u, [&](const edge &e)   // 先递归处理轻儿子及后代（下层），不加入记录
        {
            if (e.v == fa || e.v == very[u]) return;
            dfs(e.v, u, false);
        });
        if (very[u]) dfs(very[u], u, true); // 递归处理重儿子及后代，并记录
        insert(u);
        forEach(u, [&](const edge &e)   // （本层）对于其他儿子，统计和重儿子间的贡献，并记录
        {
            if (e.v == fa || e.v == very[u]) return;
            calc(e.v, u, u);
            for (auto &j : temp) insert(j);
            temp.clear();
        });
        if (!keep) clear(u, fa);    // （本层）当前子树非主要儿子，清空记录，交还上一层
    }

    auto go()
    {
        preDFS(1, 0);
        dfs(1, 0, true);
        return ans;
    }
}


signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(), u, v;
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    FWS::init(n);
    for (int i = 1; i < n; ++ i)
        scanner(u, v),
        FWS::addEdge(u, v),
        FWS::addEdge(v, u);
    println(DSUonTree::go());
    return 0;
}