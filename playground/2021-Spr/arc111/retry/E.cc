/**
 *
 * 这是一个类欧几里得的模板题
 *
 * 豆知识：向上取整除法和向下取整除法互换
 * - ceil(b / c) = floor([b + (c - 1)] / c)
 * - floor(b / c) = ceil([b - (c - 1)] / c)
 * 以及一些与之相关的转换式：
 * + ac <= b  <=>  a <= floor(b / c)
 * + ac < b   <=>  a < ceil(b / c)
 * + ac >= b  <=>  a >= ceil(b / c)
 * + ac > b   <=>  a > floor(b / c)
 * REFERENCE: https://blog.csdn.net/dreaming__ldx/article/details/86768953
 *
 * K :  K(B - C) + 1 >= D, K(min)
 * cnt: Σ i:[1, K) (iC + A) / D - (iB + A - 1) / D
 * ans: K - 1 - cnt
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

longs f(longs a, longs b, longs c, longs n)
{
    if (!a) return 0;
    auto rac = a % c, rbc = b % c;
    auto dac = a / c, dbc = b / c;
    longs ret;
    if (dac || dbc)
        ret = f(rac, rbc, c, n)
            + dac * n * (n + 1) / 2
            + dbc * (n + 1);
    else ret = (a * n + b) / c * n
        - f(c, c - b - 1, a, (a * n + b) / c - 1);
    return ret;
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
        longs a, b, c, d;
        scanner(a, b, c, d);
        auto e = c - b;
        auto k = (d - 1 + (e - 1)) / e - 1;
        auto cnt = f(c, a, d, k) - f(b, a - 1, d, k);
        println(k - cnt);
    }
    return 0;
}