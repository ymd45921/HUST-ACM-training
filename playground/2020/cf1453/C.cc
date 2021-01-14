/**
 *
 * 真不会写代码（
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

char s[2060][2060];
int ans[11], uu[11], dd[11], ll[11], rr[11];
vector<pair<int, int>> pos[11];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    while (t --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            scanner(s[i] + 1);
        memset(ans, 0, sizeof ans);
        memset(ll, 0x3f, sizeof ll);
        memset(rr, 0x00, sizeof rr);
        memset(uu, 0x3f, sizeof uu);
        memset(dd, 0x00, sizeof dd);
        for (int ii = 0; ii < 10; ++ ii)
            pos[ii].clear();
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
            {
                const auto x = s[i][j] - '0';
                maximize(rr[x], j);
                minimize(ll[x], j);
                maximize(dd[x], i);
                minimize(uu[x], i);
                pos[x].emplace_back(i, j);
            }
        for (int ii = 0; ii < 10; ++ ii)
        {
            const auto &ar = pos[ii];
            for (auto [x, y] : ar)
            {
                const auto w = max(y - 1, n - y);
                const auto h = max(x - 1, n - x);
                maximize(ans[ii],
                         w * max(x - uu[ii], dd[ii] - x),
                         h * max(y - ll[ii], rr[ii] - y));
            }
        }
        for (int ii = 0; ii < 10; ++ ii)
            print(ans[ii]), putchar(' ');
        puts("");
    }

    return 0;
}