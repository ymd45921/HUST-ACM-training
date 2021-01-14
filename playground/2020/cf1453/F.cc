/**
 *
 * 计数问题，外加一个这么经典的数据范围，问就是 DP，还是二维的
 * 那么应该怎么二维 DP 才能做出来呢（逃
 *
 * 分析：当 n 可达且方法唯一时：每个节点都有且仅有一种方法到达
 * 初始情况下，可能有多种情况到达 n 节点；那么每个节点都有多种方法到达
 * 形式化的说，有多个 j 满足 j + a[j] >= i；我们将多余的 a[j] = 0 便执行了清理
 *
 * 设 dp[i][x] 表示，到达 i 唯一的前驱可到达的最远距离小于 x 时，需要清洗的平台数量
 * 设 cnt 表示的是在区间 (j, i) 内的，可以到达 i 或更远的平台数量
 * dp[1][..] = 0：显然，对于第一个点，到达该点的方法是唯一的，不需要任何清理
 * 顺序枚举第一维度 i，从 i 开始倒序维护第二维度 j：
 * - 如果 j 可以跳转到 i 或者更右的地方，说明 j 到 tmp 的转移可行
 * - 所以 dp[i][tmp] 可以用 dp[j][i - 1] + cnt 来更新：先到达 j，清空 cnt 的平台
 * - 由定义可知，dp[i][x] 始终可以用 dp[i][x - 1] 更新，所以进行维护
 * 综上所述，维护得到的 dp[n][n] 就是答案；思路可见下图：
 *
 * //                               tmp = j + a[j]
 * //                    |================================>|
 * //       pred      <--j       cnt       i-->            |
 * // [------++----------[===x====x=x=====]||-----x--------+---]
 * //        ||          |          |…………|……………………|
 * //        ||=========>+----------->___| i-1
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

const int N = 3060;
const int inf = 0x3f3f3f3f;
int a[N], f[N][N];

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
        int n = scanner.nextInt();
        const auto siz = sizeof(int) * (n + 1);
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        for (int i = 2; i <= n; ++ i)
        {
            memset(f[i], 0x3f, siz);
            int cnt = 0, tmp;
            for (int j = i - 1; j; -- j)
                if ((tmp = j + a[j]) >= i)
                    minimize(f[i][tmp], f[j][i - 1] + cnt ++);
            for (int j = i + 1; j <= n; ++ j)
                minimize(f[i][j], f[i][j - 1]);
        }
        println(f[n][n]);
    }
    return 0;
}