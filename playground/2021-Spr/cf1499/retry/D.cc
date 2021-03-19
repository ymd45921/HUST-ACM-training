/**
 *
 * 和 exgcd 没什么关系啊……
 * 为什么我总是能想到歧路上去呢？
 *
 * 套一层 exgcd，解出了两个变量之间还有关系
 * 还要再进行其他层面的约束处理，不麻烦嘛？
 * 
 * RE: 虽然数据范围是 1e7，但是直接操作数是两个 1e7 之和
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

const int A = 2e7 + 7;

namespace linear_sieve
{
    vector<int> prime;
    array<int, A + 1> cnt;
    bitset<A + 1> vis;

    void start()
    {
        for (int i = 2; i <= A; ++ i)
        {
            if (!vis[i])
                prime.push_back(i), cnt[i] = 1;
            for (auto & pp : prime)
            {
                auto ipp = (longs)i * pp;
                if (ipp > A) break;
                vis.set(ipp);
                if (i % pp == 0)
                {cnt[ipp] = cnt[i]; break;}
                cnt[ipp] = cnt[i] + 1;
            }
        }
    }
}

longs fastPow(longs a, ulongs b)
{
    longs ans = 1;
    while (b)
    {
        if (b & 1u) ans = (ans * a);
        a = (a * a); b >>= 1u;
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt(), c, d, x;
    using linear_sieve::cnt;
    linear_sieve::start();
    const auto calc =
    [&](longs y) -> longs
    {
        if ((d + y) % c) return 0;
        const auto z = (d + y) / c;
        return fastPow(2, cnt[z]);
    };
    while (T --)
    {
        scanner(c, d, x);
        longs ans = 0, y;
        for (y = 1; y * y < x; ++ y)
            if (!(x % y))
                ans += calc(y) + calc(x / y);
        if (y * y == x) ans += calc(y);
        println(ans);
    }
    return 0;
}