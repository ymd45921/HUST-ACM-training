/**
 *
 * Pretest RE ??
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define lll __int128
#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(args...) cerr << args << endl
#define $$ << ", " <<
#define vars(x, y...) var(x) << ", " << vars(y)
#else
#define eprintf(...)
#define watch(...)
#endif

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

    static inline bool isSeparator(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = getchar(); while (isSeparator(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar()
    {int x = getchar(); while (isSeparator(x)) x = getchar(); return x;}
} scanner;

const longs mod = 998244353, N = 320000;

namespace FastC
{
    longs fact[N], inv[N];

    longs fastPow(longs a, uint b)
    {
        longs ans = 1;
        while (b)
        {
            if (b & 1u) ans = (ans * a) % mod;
            a = (a * a) % mod;
            b >>= 1u;
        }
        return ans % mod;
    }

    void init(int p)
    {
        fact[0] = 1;
        for (int i = 1; i <= p; i++)
            fact[i] = fact[i - 1] * i % mod;
        inv[p] = fastPow(fact[p], mod - 2);
        for (int i = p - 1; i >= 0; i--)
            inv[i] = inv[i + 1] * (i + 1) % mod;
    }

    longs C(longs n, longs m)
    {
        if (m > n) return 0;
        return fact[n] * inv[m] % mod * inv[n - m] % mod;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    int nn = n * 2, _n = n;
    vector<int> a;
    while (nn --)
        a.push_back(scanner.nextInt());
    sort(a.begin(), a.end());
    FastC::init(310000);
    auto ii = a.begin();
    auto jj = a.rbegin();
    longs ans = 0;
    while (_n --)
    {
        ans = (ans + *jj - *ii) % mod;
        ++ ii, ++ jj;
    }
    nn = n * 2, _n = n;
    auto combine = FastC::C(nn, _n);
    ans = (ans * combine) % mod;
#if 0
    for (auto ii : a) cerr << ii << ' ';
    cerr << endl;
    watch(var(ans));
#endif
    puti(ans);
    return 0;
}

