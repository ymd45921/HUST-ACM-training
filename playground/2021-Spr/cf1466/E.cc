/**
 *
 * 第一次完全自主的写二进制分组处理的案例
 * 打得不错！
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
void print(string &s) {printf(s.c_str());}
void print(const char *s) {printf(s);}
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

const int N = 5e5 + 5;
const int mod = 1e9 + 7;
ulongs mask[64], weigh[64];
ulongs x[N], a[64][2], b[64][2], cnt[64][2];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    for (uint i = 0; i <= 61; ++ i)
        mask[i] = 1ull << i,
        weigh[i] = mask[i] % mod;
    int T = scanner.nextInt();
    while (T --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            x[i] = scanner.nextLongs();
        memset(cnt, 0, sizeof cnt);
        ulongs all = (ulongs)n * n;
        for (int i = 1; i <= n; ++ i)
            for (int j = 0; j <= 61; ++ j)
                ++ cnt[j][bool(x[i] & mask[j])];
        lll ans = 0;
        for (int i = 1; i <= n; ++ i)
        {
            memset(a, 0, sizeof a);
            memset(b, 0, sizeof b);
            bitset<64> now = x[i];
            for (int j = 0; j <= 61; ++ j)
            {
                if (now[j]) a[j][1] = cnt[j][1];
                a[j][0] = n - a[j][i];
                if (!now[j]) b[j][0] = cnt[j][0];
                b[j][1] = n - b[j][0];
            }
            lll aa = 0, bb = 0;
            for (int j = 0; j <= 61; ++ j)
            {
                aa += a[j][1] * weigh[j] % mod;
                bb += b[j][1] * weigh[j] % mod;
                aa %= mod, bb %= mod;
            }
            ans += aa * bb % mod, ans %= mod;
        }
        println(ans);
    }
    return 0;
}