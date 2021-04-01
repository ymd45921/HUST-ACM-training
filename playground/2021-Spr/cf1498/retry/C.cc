/**
 *
 * 那么这个题没做出来就是单纯自己菜了
 * 其实也有时间不够的要素在里面）
 *
 * 如果 DP 只开两维，那么就会发现状态不能转移
 * 因为两个方向的转移不能等量齐观
 *
 * 所以最后放弃正确思路去考虑玄学做法还是我菜了（
 * 
 * 现在想想这应该不是推导型 DP，只是单纯的记忆化搜索
 * 或者不管怎么说，就是一般的由子问题求主问题
 * 之前什么 DP 都嗯递推还是菜了些（
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

const int N = 1050;

int dp[N][N][2], n, k;
const int mod = 1e9 + 7;

int solve(int pos, int kk, int dir)
{
    if (dp[pos][kk][dir]) return dp[pos][kk][dir];
    else if (kk == 1) return dp[pos][kk][dir] = 1;
    int ret = 2;
    if (dir)
    {
        if (pos > 1)
            ret += solve(pos - 1, kk - 1, 0) - 1;
        ret %= mod;
        if (pos < n)
            ret += solve(pos + 1, kk, 1) - 1;
        ret %= mod;
    }
    else
    {
        if (pos > 1)
            ret += solve(pos - 1, kk, 0) - 1;
        ret %= mod;
        if (pos < n)
            ret += solve(pos + 1, kk - 1, 1) - 1;
        ret %= mod;
    }
    return dp[pos][kk][dir] = ret;
}

#define f(x, y) dp[x][y][0]

int $solve(int nn, int kk)
{
    if (f(nn, kk)) return f(nn, kk);
    else if (kk == 1 || !nn || nn == n + 1)
        return f(nn, kk) = 1;
    int ret = 2;
    ret += $solve(n - nn, kk - 1) - 1;
    ret %= mod;
    ret += $solve(nn - 1, kk) - 1;
    return f(nn, kk) = ret %= mod;
}


signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    while (T --)
    {
        scanner(n, k);
        for (int i = 0; i <= n; ++ i)
            for (int j = 1; j <= k; ++ j)
                memset(dp[i][j], 0, sizeof(dp[i][j]));
        println($solve(n, k));
    }
    return 0;
}