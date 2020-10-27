/**
 *
 * 细节，看清题目；不要想当然（
 * 原来的代码十有八九 PP 然后 FST ==
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

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

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return (char)getchar();}
} scanner;

const int mod = 1e9 + 7;

namespace FastC
{
    const longs mod = 1e9 + 7;
    const int N = 1050;
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

    longs $C(longs n, longs m)
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
    FastC::init(1030);
    int n, x, pos;
    scanner(n, x, pos);
    int left = 0, right = n;
    int bigger = 0, smaller = 0;
    vector<int> S, B;   // log
    while (left < right)
    {
        int middle = (left + right) / 2;
        if (middle <= pos) ++ smaller, left = middle + 1, S.push_back(middle);
        else ++ bigger, right = middle, B.push_back(middle);
    }
    assert(smaller > 0);
#if 0
    cerr << var(left - 1) << ", " << var(smaller) << ", " << var(bigger) << endl;
    cerr << "SMALL: ";
    for (auto ii : S) cerr << ii << " ";
    cerr <<"\nBIG: ";
    for (auto ii : B) cerr << ii << " ";
    cerr << endl;
#endif
    if (x >= smaller && n - x >= bigger);
    else {println(0); return 0;}
    assert(smaller + bigger <= n);
    lll small = FastC::$C(x - 1, smaller - 1);
    lll big = FastC::$C(n - x, bigger);
    lll residue = n - smaller - bigger;
    using FastC::fact;
    small = small * fact[smaller - 1] % mod, big = big * fact[bigger] % mod;
    residue = fact[residue] % mod;
    lll ans = small * big % mod * residue % mod;
    println(ans);

    return 0;
}

