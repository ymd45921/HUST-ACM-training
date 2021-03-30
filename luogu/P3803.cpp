/**
 *
 * 递归嗯被我优化过了？nb
 * 
 * 之前使劲 WA 是因为我没有 round
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

const int N = 1e6 + 5;

namespace FFT
{
    using number = double;
    using complex = std::complex<number>;
    using addr = vector<complex>::iterator;

    const number PI = acosl(-1.l);
    const number eps = 0.5;

    namespace MemoryPool
    {
        vector<vector<complex>> pool;
        size_t mem_stack_top = 0, max_frame_size;

        void init_mem_pool(size_t block)
        {
            pool.reserve(ceil(log2(block)) + 1);
            max_frame_size = block;
        }

        uint stretch(uint n)
        {
            auto x = __builtin_clz(n);
            return (1u << (32u - x));
        }

        vector<complex> &stretch(vector<complex> &p)
        {return p.resize(stretch(p.size())), p;}

        vector<complex> &_alloc(size_t block = max_frame_size)
        {
            if (pool.size() == mem_stack_top)
                pool.emplace_back(block);
            return pool[mem_stack_top ++];
        }

        void _free_mem_stack_frame()
        {if (mem_stack_top) -- mem_stack_top;}
    }
    using namespace MemoryPool;

    complex getW(uint n, uint k = 1)
    {
        const auto angle = (k % n) * PI * 2 / n;
        return complex(cos(angle), sin(angle));
    }

    void subprocess(addr f, size_t n)
    {
        if (n == 1) return;
        const auto m = n / 2;
        vector<complex> &sub = _alloc(n);
        auto f0 = sub.begin(), f1 = f0 + m;
        for (int i = 0; i < m; ++ i)
            f0[i] = f[i * 2],
            f1[i] = f[i * 2 + 1];
        subprocess(f0, m);
        subprocess(f1, m);
        auto unit = getW(n), w = getW(1, 0);
        for (int i = 0; i < m; ++ i)
            f[i] = f0[i] + w * f1[i],
            f[i + m] = f0[i] - w * f1[i],
            w *= unit;
        _free_mem_stack_frame();
    }

    void start(vector<complex> &p, bool inv)
    {
        subprocess(p.begin(), p.size());
        if (inv) reverse(++ p.begin(), p.end());
    }

    void fft(vector<complex> &p)
    {start(p, false);}

    void _post_ifft(complex &ii, int n)
    {ii.real(ii.real() / n + eps);}

    void ifft(vector<complex> &p)
    {
        start(p, true);
        const auto n = p.size();
        for (auto &i : p) _post_ifft(i, n);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    vector<FFT::complex> a, b;
    const auto siz = FFT::stretch(n + m);
    a.resize(siz), b.resize(siz);
    FFT::init_mem_pool(siz);
    for (int i = 0; i <= n; ++ i)
        a[i].real(scanner.nextInt());
    for (int i = 0; i <= m; ++ i)
        b[i].real(scanner.nextInt());
    FFT::fft(a), FFT::fft(b);
    for (int i = 0; i < siz; ++ i)
        a[i] *= b[i];
    FFT::ifft(a);
    for (int i = 0; i <= n + m; ++ i)
        cout << (int)a[i].real() << " \n"[n + m == i];
    return 0;
}