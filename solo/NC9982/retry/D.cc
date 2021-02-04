/**
 *
 * 数论这块确实不熟悉，所以这题没做也没啥办法（
 * 但是就算不会证明整除分块的 √n 的复杂度，也不影响这个题
 * 
 * 要做这个题目需要知道有一个主要的性质：
 * + 首先，既然和数论相关，那就免不了 √n 这个关键点
 * + 求 n // k，如果 k < √n，显然 k 每变化一次，值就变化一次
 * + 当 k > √n 的时候，就是反过来，√n 个值分布在 (√n, n]，不难证明值是连续的
 * + 此外，只需要考虑 k 在跨越 √n 时的表现即可
 * 所以其实这个题目可以做到 O(1) 回答问题
 * 
 * 现在考虑 k 跨越 √n 的表现，考虑一般较大自然数 n 和 x
 * - 若 n = x²，那么 √n = x，n // √n = x，n // (x + 1) = x - 1，相差 1
 * - 若 n = x² - 1，那么 √n = x - 1，n // √n = x + 1，n // x = x - 1/x = x - 1， 相差 2
 * - 若 n = x² + 1，那么 √n = x，n // √n = x，n // (√n + 1) = (x + 1) - 2 - 2 / (x + 1)，相差 1
 * 因此，综上所述，可以推测，除了 n = x² - 1 时，变化均为 1
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
        int n = scanner.nextInt(),
            x = scanner.nextInt();
        int sq = sqrt(n);
        if (x <= sq) println(x);
        else 
        {
            int rank = sq, base = n / sq;
            int gap = base - n / (sq + 1);  // n = sq * (sq + 2) => gap == 2
            rank += abs(n / x - base) - (gap - 1);
            println(rank);
        }
    }
    return 0;
}