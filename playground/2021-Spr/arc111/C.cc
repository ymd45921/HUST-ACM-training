/**
 *
 * 经典的排序复位问题，按 i -> pi 建图
 * 那么进行交换操作复位至少需要 N - C 次
 * 其中，C 是这样建图的环数，包括自环
 *
 * 但是因为有操作限制，所以，总是让环内最轻的人优先处理
 * 最终的次数还是 N - C，所以这个题面极具误导力（
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
int a[N], b[N], p[N], m[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    vector<vector<int>> circle;
    bitset<N> vis;
    const function<void(int)> dfs =
    [&](int u) -> void
    {
        if (vis[u]) return;
        circle.back().push_back(u);
        vis[u] = true;
        dfs(p[u]);
    };
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        b[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        p[i] = scanner.nextInt(),
        m[p[i]] = i;
    bool ok = true;
    for (int i = 1; i <= n; ++ i)
        if (i != p[i] && a[i] <= b[p[i]])
        { ok = false; break; }
    if (!ok) return puts("-1"), 0;
    for (int i = 1; i <= n; ++ i)
        if (!vis[i])
            circle.emplace_back(), dfs(i);
    for (auto &ring : circle)
        sort(ring.begin(), ring.end(),
             [](int x, int y) -> bool
             {return a[x] < a[y];});
    vector<pair<int, int>> ans;
    for (auto &ring : circle)
        for (auto ii: ring)
            if (ii != p[ii])
            {
                auto jj = m[ii];
                swap(p[ii], p[jj]);
                swap(m[p[ii]], m[p[jj]]);
                ans.emplace_back(ii, jj);
            }
    println(ans.size());
    for (auto [a, b]: ans) print(a, ' ', b, '\n');
    return 0;
}