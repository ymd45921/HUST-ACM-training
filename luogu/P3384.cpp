/**
 *
 * 来自 zcysky 的树剖：
 * 
 * 首先，你已经学会了树剖求 LCA；
 * 然后，知道了树剖保证了跳链是 log 的
 * 这里就是利用树剖将树转化为区间：
 * - 树链问题：像 LCA 那样跳链，每条链是连续区间
 * - 子树问题：毕竟是 DFS 序，子树都是连续的区间
 * 所以树剖后重新标记下表，用线段树维护即可
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

const int N = 1e5 + 5, M = N;

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
    int label[N], tot = 0;

    void count(int u, int p)
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

    void link(int u, int $top)
    {
        label[u] = ++ tot;      // re-label
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

    void build(int root, int *des, const int *src)
    {
        dep[root] = 1;
        count(root, -1);
        link(root, root);
        for (int i = 1; i <= tot; ++ i) // apply new label
            des[label[i]] = src[i];     // to build seg tree
    }
}

int a[N], b[N];
longs n, m, r, p, u, v, x, y, z;

namespace segmentTree
{
    template <class T>
    struct node
    {
        int ll{}, rr{};
        T value{}, lazy{0};

        node() = default;
        node(int ll, int rr, T val)
        : ll(ll), rr(rr), value(val)
        {lazy = 0;}

        int size() {return rr - ll + 1;}
    };

    using type = int;
    using merge_t = function<type(type, type)>;
    node<type> t[N * 4];
    const type *src = b;

    void merge(uint id) // update
    {
        lll lv = t[id << 1u].value;
        lll rv = t[id << 1u | 1u].value;
        t[id].value = (lv + rv + p) % p;
    }

    void build(uint id, int l, int r)
    {
        t[id] = node(l, r, 0);
        if (l == r) {t[id].value = src[l]; return;}
        int mid = (l + r) / 2;
        build(id << 1u, l, mid);
        build(id << 1u | 1u, mid + 1, r);
        merge(id);
    }

    void apply(uint id) // push down
    {
        if (!t[id].lazy) return;
        auto &ls = t[id << 1u], &rs = t[id << 1u | 1u];
        ls.value = (ls.value + (lll)ls.size() * t[id].lazy) % p;
        rs.value = (rs.value + (lll)rs.size() * t[id].lazy) % p;
        ls.lazy = (ls.lazy + t[id].lazy) % p;
        rs.lazy = (rs.lazy + t[id].lazy) % p;
        t[id].lazy = 0;
    }

    void add(uint id, int l, int r, type x)
    {
        if (l <= t[id].ll && t[id].rr <= r)
            t[id].value = (t[id].value + (lll)t[id].size() * x) % p,
            t[id].lazy = (t[id].lazy + x) % p;
        else
        {
            apply(id);
            int mid = (t[id].ll + t[id].rr) / 2;
            if (l <= mid) add(id << 1u, l, r, x);
            if (r > mid) add(id << 1u | 1u, l, r, x);
            merge(id);
        }
    }

    type sum(uint id, int l, int r)
    {
        type ret = 0;
        if (l <= t[id].ll && t[id].rr <= r)
            return t[id].value;
        apply(id);
        int mid = (t[id].ll + t[id].rr) / 2;
        if (l <= mid) ret = (ret + (lll)sum(id << 1u, l, r)) % p;
        if (r > mid) ret = (ret + (lll)sum(id << 1u | 1u, l, r)) % p;
        return ret;
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
    scanner(n, m, r, p);
    FWS::init(n);
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    for (int i = 1; i < n; ++ i)
    {
        scanner(u, v);
        FWS::addEdge(u, v);
        FWS::addEdge(v, u);
    }
    dfsTree::build(r, b, a);
    segmentTree::build(1, 1, n);
    lll out, tmp;
    using namespace dfsTree;
    while (m --)
        switch (scanner.nextInt())
        {
            case 1: // 树上 x-y 的路径的权值 += z
                scanner(x, y, z);
                while (top[x] != top[y])
                {
                    if (dep[top[x]] < dep[top[y]])
                        swap(x, y);
                    segmentTree::add(1, label[top[x]], label[x], z % p);
                    x = fa[top[x]];
                }
                if (dep[x] > dep[y]) swap(x, y);
                segmentTree::add(1, label[x], label[y], z % p);
                break;
            case 2: // 求出树上 x-y 的路径的权值和
                scanner(x, y), out = 0;
                while (top[x] != top[y])
                {
                    if (dep[top[x]] < dep[top[y]])
                        swap(x, y);
                    auto ret = segmentTree::sum(1, label[top[x]], label[x]);
                    out = (out + ret) % p;
                    x = fa[top[x]];
                }
                if (dep[x] > dep[y]) swap(x, y);
                tmp = segmentTree::sum(1, label[x], label[y]);
                out = (out + tmp) % p;
                println(out);
                break;
            case 3: // 将以 x 为根的子树权值 += z
                scanner(x, z);
                segmentTree::add(1, label[x], label[x] + siz[x] - 1, z % p);
                break;
            case 4: // 求以 x 为根的子树的权值和
                scanner(x);
                out = segmentTree::sum(1, label[x], label[x] + siz[x] - 1);
                println(out);
                break;
        }
    return 0;
}