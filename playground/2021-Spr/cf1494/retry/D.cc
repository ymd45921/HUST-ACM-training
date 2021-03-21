/**
 *
 * 递归处理
 * 俗话说构造题的关键就是要找出那个决定性的条件：
 * - 在这个题里面就是最大的那个一定是领导的收入
 * - 其他的对子如果 lca 是领导，则说明不再一个子树
 * - 否则，它们一定在一棵树内，可以放在一起
 * 递归这个操作，直到带选择列表里只有一个数字
 * 
 * 当然，实现方面这个题也并非毫无难点：
 * - 最大的 lca 无需遍历所有的情况，任何情况下都会出现
 * - 所以只需要确定一维遍历一维就可以得到 root 的值
 * - 尝试对现在所有的节点进行划分，得到多个子树的关键值
 * - 当然，这一步可以用并查集，但是同样不自然（）
 * - 对于每个关键字找到连通块里的所有值，递归查找得到根 id
 * - 将得到的子树的根 id 和当前的 id 建立联系即可。
 * 最后，子节点会直接返回；创建的节点会返回新增节点的编号
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

struct fast_read
{
    template<class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;
#define $$ fastRead,

const int N = 550;
int a[N][N], c[N * 2];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(), k = n;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            a[i][j] = scanner.nextInt();
    vector<pair<int, int>> e;
    const function<int(vector<int> &)> process =
    [&](vector<int> &son)
    {
        const int siz = son.size();
        if (siz == 1) return c[son[0]] = a[son[0]][son[0]], son[0];
        int root = -1;
        for (int i = 0; i < siz; ++ i)
            maximize(root, a[son[0]][son[i]]);
        vector<int> tmp;
        bitset<N> vis;
        for (int i = 0; i < siz; ++ i)
        {
            bool ok = true;
            for (auto j : tmp)
                ok &= (a[j][son[i]] == root);
            if (ok) tmp.push_back(son[i]), vis.set(son[i]);
        }
        int id = ++ k; c[id] = root;
        vector<int> list;
        for (auto x : tmp)
        {
            list.clear(), list.push_back(x);
            for (auto y : son)
                if (!vis[y] && a[x][y] < root)
                    list.push_back(y);
            int now = process(list);
            e.emplace_back(now, id);
        }
        return id;
    };
    vector<int> first;
    for (int i = 1; i <= n; ++ i)
        first.push_back(i);
    auto root = process(first);
    println(k);
    for (int i = 1; i <= k; ++ i)
        print(c[i], " \n"[i == k]);
    println(root);
    for (auto [me, fa] : e)
        print(me, ' ', fa, '\n');
    return 0;
}