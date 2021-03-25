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

using dist_t = int;
using info_t = pair<dist_t, int>;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 5e5 + 5, M = N;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }
}

const dist_t inf = 0x3f3f3f3f;

namespace dfsTree
{
    using namespace FWS;

    bitset<N> vis;
    int siz[N], son[N], fa[N], dep[N], top[N];

    void count(int u, int p)    // dfs1
    {
        siz[u] = 1, vis.set(u);
        FWS::forEach(u, [&](const edge &e)
        {
            auto v = e.v;
            if (vis[v]) return;
            dep[v] = dep[u] + 1;
            fa[v] = u;
            count(v, u), siz[u] += siz[v];
            if (siz[v] > siz[son[u]]) son[u] = v;
        });
    }

    void link(int u, int $top) // dfs2
    {
        top[u] = $top;
        if (son[u]) link(son[u], $top);
        FWS::forEach(u, [&](const edge &e)
        {
            auto v = e.v;
            if (v == fa[u] || v == son[u]) return;
            link(v, v);
        });
    }

    int lca(int x, int y)
    {
        while (top[x] != top[y])
            if (dep[top[x]] < dep[top[y]])
                y = fa[top[y]];
            else x = fa[top[x]];
        return dep[x] < dep[y] ? x : y;
    }

    void run(int root)
    {
        dep[root] = 1;
        count(root, -1);
        link(root, root);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt(),
        s = scanner.nextInt();
    FWS::init(n);
    for (int i = 1; i < n; ++ i)
    {
        int u = scanner.nextInt(),
            v = scanner.nextInt();
        FWS::addEdge(u, v);
        FWS::addEdge(v, u);
    }
    dfsTree::run(s);
    while (m --)
    {
        int x = scanner.nextInt(),
            y = scanner.nextInt();
        println(dfsTree::lca(x, y));
    }
    return 0;
}