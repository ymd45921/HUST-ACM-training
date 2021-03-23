/**
 *
 * 首先用 O(n, k) 的时间求出 ll 数组：
 * - ll[i][j] 的定义是从 i 往前，允许修改 j 次，可以到达的最远的位置
 * - 首先，因为有很多质数，所以修改成任意值可以认为是使得冲突消失而不引入新冲突
 * - 所以，可以贪心的预处理出 ll 数组：[ll[r][j], r] 只需要处理 j 次
 * 然后就用处理的 ll 更新 DP 数组：
 * - 从前向后扫描：f[i][j] 表示长度为 i 的前缀允许不超过 j 次修改的答案
 * - 显然，f[0] 为 0；[ll[r][j], r] 段将会用掉 j 次修改机会
 * - 显然，对于 j > 0，f[i][j] 可由 f[i][j - 1] 转移而来
 * - 记 l = ll[i]；那么所有的 k <= j, f[l[k] - 1] + 1 都可以转移到 f[i][j]
 * 所以这个题目就可以 O(nk) 预处理，O(nk²) 求解。
 *
 * 原来这场是 SpeedForces 啊
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

const int N = 2e5 + 5, A = 1e7 + 7;
int a[N], pattern[N], cnt[A];
int ll[N][25], f[N][25];

// PrimeFactorizationSieve()
namespace PFS
{
    vector<int> prime;
    array<int, A + 1> fact;

    void start()
    {
        for (int i = 2; i <= A; ++ i)
        {
            if (!fact[i])
                prime.push_back(i), fact[i] = i;
            for (auto & pp : prime)
            {
                if ((longs)i * pp > A) break;
                fact[i * pp] = pp;
                if (i % pp == 0) break;
            }
        }
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
    int T = scanner.nextInt();
    using PFS::prime, PFS::fact;
    PFS::start();
    while (T --)
    {
        int n = scanner.nextInt(),
            k = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        fill(pattern, pattern + n + 1, 1);
        for (int i = 1; i <= n; ++ i)
        {
            int exp = 0, base = 0, tmp = a[i];
            while (tmp > 1)
            {
                int p = fact[tmp];
                if (base == p) ++ exp;
                else
                {
                    if (exp % 2) pattern[i] *= base;
                    base = p, exp = 1;
                } tmp /= p;
            }
            if (exp % 2) pattern[i] *= base;
        }
        for (int j = 0; j <= k; ++ j)
        {
            int cur = n + 1, use = 0;
            for (int i = n; i > 0; -- i)
            {
                while (cur - 1 >= 1 &&
                       use + !!cnt[pattern[cur - 1]] <= j)
                    use += !!(cnt[pattern[-- cur]] ++);
                ll[i][j] = cur;
                if (cnt[pattern[i]] --> 1) -- use;
            }
        }
        for (int i = 1; i <= n; ++ i)
            memset(f[i], 0x3f, sizeof(f[i]));
        memset(f[0], 0, sizeof(f[0]));
        for (int i = 1; i <= n; ++ i)
            for (int j = 0; j <= k; ++ j)
            {
                if (j) minimize(f[i][j], f[i][j - 1]);
                for (int l = 0; l <= j; ++ l)
                    minimize(f[i][j], f[ll[i][l] - 1][j - l] + 1);
            }
        int ans = 0x3f3f3f3f;
        for (int i = 0; i <= k; ++ i)
            minimize(ans, f[n][i]);
        println(ans);
    }
    return 0;
}