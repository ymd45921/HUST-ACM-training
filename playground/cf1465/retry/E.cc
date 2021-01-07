/**
 *
 * 最后应该是 -*..-+ 的形式
 * - 因此，除去所有的前缀 -
 * - 每次划分都从连续的 - 的第一个之后
 * - 因此，前面的实际上可以是任何组合
 * - 唯一限制条件是最后两位
 * 这样就可以递归的划分
 *
 * 现在，问题变成了使用给定字符串的前 n-2 个来构造数字
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

#define pos(x) ((x) - 'a')
#define sig(x) (sgn(x) ? sgn(x) : 1)

const int N = 1e5 + 5;
char s[N];
lll f[27];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    f[0] = 1;
    for (int i = 1; i <= 26; ++ i)
        f[i] = f[i - 1] * 2;
    lll T; int n;
    scanner(n, T, s + 1);
    lll tmp = -f[pos(s[n - 1])] + f[pos(s[n])];
    const int lim = n - 2;
    array<int, 26> cnt{};
    for (int i = 1; i <= lim; ++ i)
        ++ cnt[pos(s[i])];
    lll d = T - tmp;
    for (int i = 25; i >= 0; -- i)
    {
        int ii = cnt[i];
        bool odd = ii % 2;
        int time = ii / 2;
        lll step = f[i] * 2;
        if (odd) d -= sig(d) * f[i];
        while (time --) d -= sgn(d) * step;
    }
    println(d ? "No" : "Yes");
    return 0;
}