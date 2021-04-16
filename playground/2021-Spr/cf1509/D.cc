/**
 *
 * 真的假了，，，
 * 
 * 假设三个字符串 a, b, c
 * 假设 a 和 b 不同的位数为 x：
 * - x <= n: 相同的位置一份，不相同的位置两份
 * - x > n: 字符串不能由 a 和 b 拼凑成，考虑 c
 *   - c 和 a 和 b 最大的不同情况是这样的：
 *     - a 和 b 相同的 (2n - x) 和 c 完全不同
 *     - a 和 b 不同的 x 位 c 分别和 a 和 b 有 x/2 处不同
 *     - 如果偏向一边，因为是 01 串，就会和另一边相同
 *   - 综上所述 c 和 a/b 最小不同数的最大值是 (2n - x) + 
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

const int N = 4e5 + 5;
char a[N], b[N], c[N], ans[N];

bool build(const char *aa, const char *bb, int n)
{
    int len = n * 2, lim = 3 * n;
    int curA = 0, curB = 0, pos = 0;
    for (int i = 0; i < len; ++ i)
    {
       ans[pos ++] = aa[i];
       if (aa[i] != bb[i]) ans[pos ++] = bb[i];
    }
    ans[pos] = '\0';
    return pos <= lim;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt(), n;
    while (T --)
    {
        scanner(n, a, b, c);
        if (build(a, b, n))
        {println(ans); continue;}
        else if (build(b, a, n))
        {println(ans); continue;}
        else if (build(a, c, n))
        {println(ans); continue;}
        else if (build(c, a, n))
        {println(ans); continue;}
        else if (build(b, c, n))
        {println(ans); continue;}
        else if (build(c, b, n))
        {println(ans); continue;}
        else watch(-1);
    }

    return 0;
}