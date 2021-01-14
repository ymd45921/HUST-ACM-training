/**
 *
 * 相当白给的一个题目；不知道比赛的时候我到底在担忧什么（
 * 算了，我撤回前言，我知道我在想什么 ==
 *
 * 首先读题，一个贡献为分值带来 2 点贡献，每一个无用字符造成 1 点损失
 *
 * 标准的 LCS，就是枚举 DP 之后的公共子序列；
 * DP[i][j] 的意义是两个字符串的前缀的公共子序列，答案就是 DP[n][m]；
 * 我们虽然是求的两个子串，假设还是两个字符串的前缀；
 * 对于前缀，有一对前缀对贡献为负，那么就可以忽略它的贡献（子串定义）
 * 所以即使是求出最优子串，但是还是可以使用上面的 DP。
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

#if 0
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

const int N = 5050;
int f[N][N];
char s1[N], s2[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    char *a = s1 + 1, *b = s2 + 1;
    scanner(n, m, a, b);          // 哈哈，几把
    watch(n, m, a, b);
    s1[0] = s2[0] = '%';
    watch(s1, s2);
    const auto siz = sizeof(int) * (m + 1);
    for (int i = 0; i <= n; ++ i)
        memset(f[i], 0, siz);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            maximize(f[i][j], f[i - 1][j] - 1, f[i][j - 1] - 1),
            (s1[i] == s2[j]) && maximize(f[i][j], f[i - 1][j - 1] + 2);
    int ans = 0;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= m; ++ j)
            eprintf("%d ", f[i][j]);
        eputs("");
    }
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            maximize(ans, f[i][j]);
    println(ans);
    return 0;
}