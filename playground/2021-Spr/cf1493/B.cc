/**
 *
 *
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

char trans[] = {'0', '1', '5', '-', '-', '2', '-', '-', '8', '-'};

void mirror(const char *s, char *t)
{
    for (int i = 0; i < 5; ++ i)
        if (s[i] == ':') t[4 - i] = ':';
        else t[4 - i] = trans[s[i] - '0'];
    t[5] = 0;
}

auto turn(const char *s)
{
    int H = (s[0] - '0') * 10 + s[1] - '0',
        M = (s[3] - '0') * 10 + s[4] - '0';
    return make_pair(H, M);
}

void make(int H, int M, char *s)
{
    s[0] = H / 10 % 10 + '0';
    s[1] = H % 10 + '0';
    s[3] = M / 10 % 10 + '0';
    s[4] = M % 10 + '0';
    s[2] = ':', s[5] = 0;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt(), h, m;
    const auto validator =
    [&](const char *s)
    {
        for (int i = 0; i < 5; ++ i)
            if (s[i] == '-') return false;
        auto [H, M] = turn(s);
        return H >= 0 && H < h && M >= 0 && M < m;
    };
    const auto tik =
    [&](char *s)
    {
        auto [H, M] = turn(s);
        ++ M; H = (H + M / m) % h;
        M %= m;
        make(H, M, s);
    };
    while (T --)
    {
        char s[6], t[6];
        $$ h, m, s;
        mirror(s, t);
        while (!validator(t))
            tik(s), mirror(s, t);
        println(s);
    }
    return 0;
}