/**
 *
 * 500 * 500 = 2.5e4
 * 真有你的（
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

const int N = 3e6 + 5;
const int mod = 1e9 + 7;
longs fact[N];
char g[550][550];

namespace DSU
{
    int fa[N], siz[N], tot = 0;
    unordered_map<int, int> comp;

    void init(int n)
    {
        for (int i = 0; i <= n; ++ i)
            fa[i] = i, siz[i] = 0;
        tot = 0, comp.clear();
    }

    int father(int u)
    {return fa[u] == u ? u : (fa[u] = father(fa[u]));}

    void join(int x, int y)
    {
        int fx = father(x), fy = father(y);
        if (fx == fy) return;
        else -- tot;
        if(!-- comp[siz[fy]]) comp.erase(siz[fy]);
        if (!-- comp[siz[fx]]) comp.erase(siz[fx]);
        if (siz[fx] <= siz[fy]) fa[fx] = fy, ++ comp[siz[fy] += siz[fx]];
        else fa[fy] = fx, ++ comp[siz[fx] += siz[fy]];
    }
}

longs fastPow(longs a, uint b)
{
    longs ans = 1;
    while (b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    const auto add = [&](int x, int y)
    {
        DSU::siz[x * n + y] = 1;
        ++ DSU::comp[1], ++ DSU::tot;
    };
    const auto adj = [&](int x, int y)
    {
        int id = x * n + y;
        if (x > 0 && g[x - 1][y] == '1')
            DSU::join(id, id - n);
        if (y > 0 && g[x][y - 1] == '1')
            DSU::join(id, id - 1);
        if (x < n - 1 && g[x + 1][y] == '1')
            DSU::join(id, id + n);
        if (y < n - 1 && g[x][y + 1] == '1')
            DSU::join(id, id + 1);
    };
    for (int i = 0; i < n; ++ i)
        scanner(g[i]);
    fact[0] = 1;
    for (int i = 1; i < N; ++ i)
        fact[i] = fact[i - 1] * i % mod;
    DSU::init(n * n + 1);
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            if (g[i][j] == '1') add(i, j);
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < n; ++ j)
            if (g[i][j] == '1') adj(i, j);
    int k = scanner.nextInt(), x, y;
    lll ans = 0;
    const auto update = [&]()
    {
        ans = fact[DSU::tot];
        for (auto [k, v] : DSU::comp)
            ans = (ans * fastPow(k, v)) % mod;
    }; update();
    while (k --)
    {
        scanner(x, y);
        if (g[x][y] == '0')
        {
            g[x][y] = '1';
            add(x, y), adj(x, y);
            update();
        }
        println(ans);
    }
    return 0;
}