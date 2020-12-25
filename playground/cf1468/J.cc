/**
 *
 * WA2: 瞎搞不太行…… 可是这难道不是贪心🐎
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

const int N = 2e5 + 5;
using edge = pair<int, pair<int, int>>;
int fa[N];

int father(int u)
{return u == fa[u] ? u : (fa[u] = father(fa[u]));}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    vector<edge> e;
    vector<int> select;
    const auto kruskal = [&](int n)
    {
        const int m = e.size();
        for (int i = 0; i < m; ++ i)
        {
            const auto &[w, ii] = e[i];
            const auto &[u, v] = ii;
            if (father(u) != father(v))
            {
                select.push_back(i);
                if (-- n == 1) break;
                fa[v] = u;
            }
        }
    };
    while (T --)
    {
        int n, m, k, x, y, s;
        scanner(n, m, k);
        e.clear(), select.clear();
        while (m --)
        {
            scanner(x, y, s);
            e.emplace_back(s, make_pair(x, y));
        }
        for (int i = 1; i <= n; ++ i) fa[i] = i;
        sort(e.begin(), e.end());
        kruskal(n);
        if (e[select.back()].first >= k)
            println(e[select.back()].first - k);
        else
        {
            edge kk = make_pair(k, make_pair(0, 0));
            int off = lower_bound(e.begin(), e.end(), kk) - e.begin();
            m = e.size();
            int ans = k - e[select.back()].first;
            if (off < m) minimize(ans, e[off].first - k);
            if (off > 0) minimize(ans, k - e[off - 1].first);
            println(ans);
        }
    }
    return 0;
}