/**
 *
 * 可以说是裸的最短路，问就是怎么建图（
 * + 首先，1e5 个 vector 是肯定跑不掉的，存区间也没什么问题
 * + 那么可以使用双指针，遍历上一行的同时维护下一行的指针
 * 这样每个数组最多只会扫描 2 次，可以说是 O(n) 建图
 * 
 * WA: 没有考虑一对多的情况
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

const int N = 1e5 + 5, M = N * 4;
vector<tuple<int, int, int>> g[N];

#define L(t) get<0>(t)
#define R(t) get<1>(t)
#define id(t) get<2>(t)

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;
using list_t = vector<int>;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

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

bitset<N> vis;
dist_t dis[N];
const dist_t inf = 0x3f3f3f3f;

void dijkstra(int st, int n)
{
    memset(dis, 0x3f, sizeof(dist_t) * (n + 1));
    heap_t heap; vis.reset();
    dis[st] = 0, heap.push({0, st});
    while (!heap.empty())
    {
        auto now = heap.top();
        heap.pop();
        const auto u = now.second;
        if (vis[u]) continue;
        else vis[u] = true;
        FWS::forEach(u, [&](const edge &e)
        {
            const auto v = e.v;
            if (dis[u] + e.w >= dis[v]) return;
            dis[v] = dis[u] + e.w;
            heap.push({dis[v], v});
        });
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
    int n, y, l, r, h = 0;
    scanner(n);
    FWS::init(n + 1);
    for (int i = 1; i <= n; ++ i)
        scanner(y, l, r),
        g[y].emplace_back(l, r, i),
        maximize(h, y);
    for (int i = 0; i <= h; ++ i)
        sort(g[i].begin(), g[i].end());
    for (int i = 0; i <= h; ++ i)
    {
        int siz1 = g[i].size(), siz2 = g[i + 1].size();
        int cur = 0;
        for (int j = 0; j < siz1; ++ j)
        {
            while (cur < siz2 && 
                R(g[i + 1][cur]) <= L(g[i][j]))
                ++ cur;
            while (cur < siz2 && R(g[i][j]) > L(g[i + 1][cur]))
            {
                FWS::addEdge(id(g[i][j]), id(g[i + 1][cur])),
                FWS::addEdge(id(g[i + 1][cur]), id(g[i][j]));
                if (R(g[i][j]) > R(g[i + 1][cur])) ++ cur;
                else break;
            }
            if (j && R(g[i][j - 1]) == L(g[i][j]))
                FWS::addEdge(id(g[i][j - 1]), id(g[i][j])),
                FWS::addEdge(id(g[i][j]), id(g[i][j - 1]));    
        }
    }
    dijkstra(1, n);
    println(dis[n] == inf ? -1 : dis[n]);        
    return 0;
}