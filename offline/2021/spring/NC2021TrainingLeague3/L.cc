/**
 *
 *  不得不说它的构造方法还是值得我学习的
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

namespace ST
{
    template <class LG>
    void calcLog(LG &lg, int n)
    {
        lg[0] = -1;
        for (int i = 1; i <= n; ++ i)
            lg[i] = lg[i / 2] + 1;
    }

    template <class rmq, class LG, class fun>
    void build(rmq &st, LG &lg, int n, const fun merge)
    {
        const uint depth = lg[n] + 1;
        for (uint l = 1; l <= depth; ++ l)
            for (uint i = 1; i + (1u << l) - 1 <= n; ++ i)
                st[i][l] = merge(st[i][l - 1], st[i + (1u << l - 1)][l - 1]);
    }

    template <class rmq, class LG, class fun>
    auto query(rmq &st, LG &lg, int l, int r, const fun merge)
    {
        const uint depth = lg[r - l + 1];
        return merge(st[l][depth], st[r - (1u << depth) + 1][depth]);
    }

    template <class rmq, class LG, class fun>
    auto bind(rmq &st, LG &lg, const fun merge)
    {
        return make_pair([&](int n){              build(st, lg, n, merge);},
                         [&](int l, int r){return query(st, lg, l, r, merge);});
    }

    template <class T>
    using closure = pair<function<void(int)>, function<T(int, int)>>;
} // namespace ST

const int N = 1e5 + 5;
longs tab[2][8][N][20], lg2[N];
const int mul[] = {0, 0, 1, 2, 3, 2, 1, 0};
vector<ST::closure<longs>> ma, mi;

longs price(int v, int d, int days)
{return v + (longs)d * mul[days % 7];}

longs fo(int s, int t, int d)
{
    const auto mid = (s + t) / 2;
    return max(
    {
        ma[d % 7].second(mid + 1, t) - 
        mi[d % 7].second(s, mid),
        fo(s, mid, d), 
        fo(mid + 1, t, d)
    });
}

longs re(int s, int t, int d)
{
    const auto mid = (s + t) / 2;
    return max(
    {
        ma[d % 7].second(t, mid) - 
        mi[d % 7].second(mid + 1, s),
        re(s, mid, d), 
        re(mid + 1, t, d)
    });
}

longs &MAX(longs &a, longs &b)
{return a < b ? b : a;}

longs &MIN(longs &a, longs &b)
{return a < b ? a : b;}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    ST::calcLog(lg2, N - 1);
    using merge_t = const longs&(*)(const longs&, const longs&);
    const merge_t $max = max<longs>, $min = min<longs>;
    for (int i = 1; i <= n; ++ i)
    {
        int v = scanner.nextInt(), 
            d = scanner.nextInt();
        for (int j = 0; j < 7; ++ j)
            tab[1][j][i][0] = tab[0][j][i][0] = price(v, d, i + 7 - j);
    }
    for (int i = 0; i < 7; ++ i)
        ma.push_back(ST::bind(tab[0][i], lg2, $max)),
        mi.push_back(ST::bind(tab[1][i], lg2, $min));
    for (auto &[gen, rmq] : ma) gen(n);
    for (auto &[gen, rmq] : mi) gen(n);
    int q = scanner.nextInt();
    while (q --)
    {
        int s = scanner.nextInt(),
            t = scanner.nextInt();
        if (s != t)
            if (s < t) println(fo(s, t, s % 7));
            else println(re(s, t, s % 7));
        else println(0);
    }
    return 0;
}