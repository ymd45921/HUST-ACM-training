/**
 *
 * 我说怎么比赛的时候过不了，原来队友读了假题
 * 
 * 但是这真的是一道优秀的题目，至少对于现在的我们的队伍来说
 * 首先有一些严肃的问题
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

constexpr longd eps = 1e-8;

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t;
    longd n;
    pair<longd, longd> a1, a2;
    cout << fixed << setprecision(10);
    const auto solo = [&](pair<longd, longd> &info) -> longd
    {
        auto [p, v] = info;
        return (min(p, n - p) + n) / v;
    };
    const auto combine = [&](pair<longd, longd> &a, pair<longd, longd> &b) -> bool
    {
        if (a > b) swap(a, b);
        return a.second >= b.first && a.first <= 0 && b.second >= n;
    };
    const auto check = [&](longd time) -> bool
    {
        auto [p1, v1] = a1; auto [p2, v2] = a2;
        longd s1 = v1 * time, s2 = v2 * time;
        auto seg1 = make_pair(p1 - s1, p1);
        auto seg2 = make_pair(p2, p2 + s2);
        if (seg1.first <= 0)
        {
            maximize(seg1.second, -seg1.first, (s1 + p1) / 2);
            minimize(seg1.second, n);
            seg1.first = 0;
        }
        if (seg2.second >= n)
        {
            minimize(seg2.first, 2 * n - seg2.second, (n + p2 - s2) / 2);
            maximize(seg2.first, 0.l);
            seg2.second = n;
        }
        return combine(seg1, seg2);
    };
    const auto metInCenter = [&]() -> longd
    {
        auto [p1, v1] = a1;auto [p2, v2] = a2;
        auto cen = p2 - p1, time = cen / (v1 + v2);
        auto pos = p1 + time * v1;
        time += max(pos / v1, (n - pos) / v2);
        return min(time, max((n - p1) / v1, p2 / v2));
    };
    for (cin >> t; t --;)
    {
        cin >> n >> a1.first >> a1.second
            >> a2.first >> a2.second;
        if (a1.first > a2.first)
            swap(a1, a2);
        longd ans = min({solo(a1), solo(a2), metInCenter()});
        longd ll = 0, rr = ans;
        int limit = 10000;
        while (limit -- && ll < rr - eps)
        {
            auto mid = (ll + rr) / 2;
            if (check(mid))
                minimize(ans, mid), rr = mid;
            else ll = mid;
        }
        cout << ans << endl;
    }
    return 0;
}