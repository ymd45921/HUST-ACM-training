/**
 *
 * 越是这种“简单”的题目就越看不透
 * 
 * 考虑到以 i 和 j 为根的最短路径树，同时满足两个条件
 * - i 和 j 之间的最短路是唯一确定的，满足到两点之和为 dis[i, j]
 *   - 如果不唯一确定，就说明存在除了最短路之外的一个点，可以取代路上的一个点
 *   - 也就是说这个点和被替换的点以及链接的点构成了一个环
 *   - 因为树不能存在环，所以必然要破开此环，这样就会损失一条最短路，不和题意
 * - 那么，除了这条最短路径上的点对答案造成的贡献应该如何计算呢？
 *   - 首先我们确定 i 和 j；然后对于每一对扫描所有的边：
 *   - 考虑最短路径树连通块上有一个点 v，有一条边 (u, v)，u 不在树上
 *   - 那么 u 可以通过这条边加入最短路径树的要求显然如下：
 *     - dis[i, u] = dis[i, v] + 1 && dis[j, u] = dis[j, v] + 1
 *     - 当然，u 也可以通过别的边加入最短路径树；我们统计可以使得 u 加入的边数
 *   - 因为每个点最后都会通过一条边加入最短路径树，所以乘起来就行了
 * - 因为 i 和 j 之间的最短路必须要按照确定的方法连接，所以没有选择权力
 * - 因此连乘过程中需要跳过这些在 i-j 最短路径上的点，它们满足到两点之和为 dis[i, j]
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
    template <class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;

#define $$ fastRead,
#define int$(...) int __VA_ARGS__; $$ __VA_ARGS__
#define i64$(...) longs __VA_ARGS__; $$ __VA_ARGS__
#define lll$(...) lll __VA_ARGS__; $$ __VA_ARGS__

using dist_t = int;
const int N = 500, M = N * 2;
const dist_t inf = 0x3f3f3f3f;
const int mod = 998244353;

dist_t dis[N][N];
int ans[N][N], layer[N];

void floyd(int n)
{
    for (int k = 1; k <= n; ++ k)
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                minimize(dis[i][j], dis[i][k] + dis[k][j]);
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    bitset<N> connect;
    vector<pair<int, int>> edge;
    const auto answer = 
    [&](int i, int j)
    {
        connect.reset();
        memset(layer, 0, sizeof(int) * (n + 1));
        for (int k = 1; k <= n; ++ k)
            if (dis[i][k] + dis[k][j] == dis[i][j])
                connect.set(k);
        if (connect.count() > dis[i][j] + 1) 
            return void(ans[i][j] = ans[j][i] = 0);
        for (auto &[u, v] : edge)
        {
            if (dis[i][u] == dis[i][v] + 1 &&
                dis[j][u] == dis[j][v] + 1)
                ++ layer[u];
            if (dis[i][v] == dis[i][u] + 1 &&
                dis[j][v] == dis[j][u] + 1)
                ++ layer[v];
        }
        longs tmp = 1;
        for (int i = 1; i <= n; ++ i)
            if (!connect[i]) tmp = tmp * layer[i] % mod;
        return void(ans[i][j] = ans[j][i] = tmp);
    }; 
    for (int i = 1; i <= n; ++ i)
        memset(dis[i], 0x3f, sizeof(int) * (n + 1)),
        dis[i][i] = 0;
    while (m --)
    {
        int u = scanner.nextInt(),
            v = scanner.nextInt();
        dis[u][v] = dis[v][u] = 1; 
        edge.emplace_back(u, v);
    }    
    floyd(n);
    for (int i = 1; i <= n; ++ i)
        for (int j = i; j <= n; ++ j)
            answer(i, j);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            print(ans[i][j], " \n"[j == n]);
    return 0;
}