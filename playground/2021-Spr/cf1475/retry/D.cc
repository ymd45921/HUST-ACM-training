/**
 *
 * 确实是贪心，但是你贪的不是很对（
 * 岂止是不对，简直错离谱了：能过样例也是因为代码写错了）
 * 不对，标答怎么一股暴力的样子 ==
 *
 * 反正总是要选一些 2 费和 1 费的，枚举查询就行了
 * 
 * 不开 long long 两行泪（被hack力
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

const int N = 2e5 + 5;
struct app {int a, b;} x[N];
longs aa[N], bb[N];

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
            m = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            x[i].a = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            x[i].b = scanner.nextInt();
        int cnt1 = 0, cnt2 = 0;
        for (int i = 1; i <= n; ++ i)
            if (x[i].b == 2) bb[++ cnt2] = x[i].a;
            else aa[++ cnt1] = x[i].a;
        sort(aa + 1, aa + 1 + cnt1, greater<>());
        sort(bb + 1, bb + 1 + cnt2, greater<>());
        for (int i = 1; i <= cnt1; ++ i) aa[i] += aa[i - 1];
        for (int i = 1; i <= cnt2; ++ i) bb[i] += bb[i - 1];
        int ans = 0x3f3f3f3f, b = cnt2;
        while (bb[b - 1] >= m) -- b;
        for (int a = 0; a <= cnt1; ++ a)
        {
            if (aa[a] >= m) {minimize(ans, a); break;}
            int res = m - aa[a];
            while (b && bb[b - 1] >= res) -- b;
            if (aa[a] + bb[b] >= m) minimize(ans, a + 2 * b);
        }
        println(ans == 0x3f3f3f3f ? -1 : ans);
    }
    return 0;
}