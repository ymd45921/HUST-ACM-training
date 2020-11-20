/**
 *
 * 哈哈，几把
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
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
    map<int, deque<int>> pos;
    vector<pair<int, int>> cnt;
    vector<int> a;
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a.push_back(scanner.nextInt()),
        pos[a.back()].push_back(i);
    if (pos.size() <= 1) return println(0), 0;
    cnt.reserve(pos.size());        // 在循环中修改 vector，应当进行预分配
    for (auto &ii : pos)
        cnt.emplace_back(ii.second.size(), ii.first);
    sort(cnt.begin(), cnt.end());
    auto &mass = cnt.back(), &after = cnt[pos.size() - 2];
    int delta = mass.first - after.first;
    if (!delta) println(n);
    else
    {
        auto &opt = pos[mass.second];
        const int xl = pos[after.second].front(),
                  xr = pos[after.second].back();
        opt.push_back(n + 1), opt.push_front(0);
        int lim = after.first, ans = 0, lp = 1;
        auto ll = opt.begin(), rr = ++ opt.begin();
        const auto end = opt.end();
        const auto calc = [&xl, &xr](int ll, int rr)
        {
            if (ll > xl || rr < xr) return 0;
            return rr - ll + 1;
        };
        while (lim --) ++ rr;
        while (rr <= end)
        {
            maximize(ans, calc(lp, *rr - 1));
            ++ ll, ++ rr, lp = *ll;
        }
        println(ans);
    }
    return 0;
}