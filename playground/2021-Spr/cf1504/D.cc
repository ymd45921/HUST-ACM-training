/**
 *
 * 这题也不难啊，就是单纯看错了题……
 * 如果必须遵守输入的颜色，那可以证明这个题不可做了（
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
    template <class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;

#define $$ fastRead,
#define int$(...) int __VA_ARGS__; $$ __VA_ARGS__
#define i64$(...) longs __VA_ARGS__; $$ __VA_ARGS__
#define lll$(...) lll __VA_ARGS__; $$ __VA_ARGS__

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, b, x, y, a;
    cin >> n;
    const int t = n * n;
    int T = t;
    queue<pair<int, int>> pos1, pos2;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            ((i + j) % 2 ? pos2 : pos1).emplace(i, j);
    while (T --)
    {
        cin >> a;
        switch (a)
        {
            case 1:
                if (!pos2.empty()) 
                    x = pos2.front().first, 
                    y = pos2.front().second, 
                    b = 2, pos2.pop();
                else
                    x = pos1.front().first, 
                    y = pos1.front().second, 
                    b = 3, pos1.pop();
                break;
            case 2:
                if (!pos1.empty())
                    x = pos1.front().first, 
                    y = pos1.front().second, 
                    b = 1, pos1.pop();
                else
                    x = pos2.front().first, 
                    y = pos2.front().second, 
                    b = 3, pos2.pop();
                break;
            case 3:
                if (!pos1.empty())
                    x = pos1.front().first, 
                    y = pos1.front().second, 
                    b = 1, pos1.pop();
                else
                    x = pos2.front().first, 
                    y = pos2.front().second, 
                    b = 2, pos2.pop();
                break;
            default: break;
        }
        cout << b << ' ' << x << ' ' << y << endl;
    }
    return 0;
}