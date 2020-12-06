/**
 *
 * 感觉像二分，那么问就是怎么判断答案合理性
 * 移动策略，最后访问深度最小的子树；因为这样回去的快
 * 但是这样就会吃到最长链+1的深度，所以可能不这样
 *
 * 简单的说：当前节点分为根和非根两种情况：
 * + 当前节点非根：当前节点是某节点的子节点
 * + 当前节点的子树访问完了，总是需要 +1 的步长：进入表兄弟或返回上一层
 * + 所以选择当前子树没有意义，所有的情况都是需要 +1 步长
 * - 当前节点为根：所有子树访问完成后只需要返回这个节点
 * - 选择深度最大的子树作为最后一棵，其他的节点只需要计算跳转步长
 * - 这样避免了最大深度 +1 步长，还需要计算次长 +1 后的长度
 * 需要注意这里的最大深度是根据子树的最浅深度来计算的，不是树高
 *
 * 就代码来看：
 * - me[] 维护了以每个节点为根的子树中最短的链长度，记作 me
 * - dfs::[mx, smx, mn] 维护了直系子树的最长、次长、最短的 me
 * - 如果是非根节点，因为所有节点都有 +1 步长，所以用 mx + 1 更新答案
 * - 如果是根节点，我们选择最大 me 的链返回，所以次大链开始都有 +1 步长
 * 这样 DFS，更新答案就可以得到需要的结果。
 *
 * 确实和秦皇岛那个题有点像，在树上贪心
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
void print(char *s) {printf(s);}
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

const int N = 2e5 + 5, M = N;
const int INF = 0x3f3f3f3f;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N], in[N], out[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(in, 0, sizeof(int) * (n + 1));
        memset(out, 0, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
        ++ out[u], ++ in[v];
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

int me[N], ans;

void dfs(int fa, int u)
{
    if (u != 1 && FWS::in[u] == 1)
        return void(me[u] = 1);
    using namespace FWS;
    int mx = 0, smx = 0, mn = me[u] = INF;
    forEach(u, [&](const edge &e)
    {
        if (e.v == fa) return;
        dfs(u, e.v);
        minimize(me[u], me[e.v] + 1);
        minimize(mn, me[e.v]);
        if (me[e.v] >= mx)
            smx = mx, mx = me[e.v];
        else if (me[e.v] > smx)
            smx = me[e.v];
    });
    if (out[u] - bool(fa) > 1)
        if (u == 1) maximize(ans, mx, smx + 1);
        else maximize(ans, mx + 1);
    else maximize(ans, mx);
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    while (t --)
    {
        const int n = scanner.nextInt();
        FWS::init(n), ans = 0;
        for (int i = 1; i < n; ++ i)
        {
            int u, v; scanner(u, v);
            FWS::addEdge(u, v);
            FWS::addEdge(v, u);
        }
        dfs(0, 1);
        println(ans);
    }
    return 0;
}