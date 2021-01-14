/**
 *
 * 没什么好说的 ==
 * 因为 dijkstra 算法复杂度是 #E·log(#V)
 * 所以稀疏图中，n 遍 dij 比 floyd 快
 * 
 * WA: wdnmd，按照 2 步长遍历 ee 不太行
 * 
 * 重写的多参数 min 可以使用 min({}) 代替
 * 可以使用已经有的新语法 auto [] = {}
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

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

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return (char)getchar();}
} scanner;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 1060, M = N;
const int inf = 0x3f3f3f3f;

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

#define P_QUEUE priority_queue
#define HEAP(T, cmp) P_QUEUE<T, vector<T>, cmp<>>
#define NODE_INFO pair<int, int>
#define weigh first     // 对于 NODE_INFO，必要时展开
#define togo second     // 对于 NODE_INFO，必要时展开

namespace ShortestPath
{
    int n;
    using node_t = NODE_INFO;
    using heap_t = HEAP(NODE_INFO, greater);
    using namespace FWS;

    template <class _n_n_Array>
    void floyd(_n_n_Array dis)
    {
        for (int k = 1; k <= n; ++ k)
            for (int i = 1; i <= n; ++ i)
                for (int j = 1; j <= n; ++ j)
                    minimize(dis[i][j], dis[i][k] + dis[k][j]);
    }

    template <class _n_Array>
    void dijkstra(int st, _n_Array dis)
    {
        for (int i = 0; i <= n; ++ i) dis[i] = inf;
        bitset<N> vis; heap_t heap;
        dis[st] = 0, heap.push({0, st});
        while (!heap.empty())
        {
            auto now = heap.top();
            heap.pop();
            const auto u = now.togo;
            if (vis[u]) continue;
            else vis[u] = true;
            forEach(u, [&](const edge &e)
            {
                const auto v = e.v;
                if (dis[u] + e.w >= dis[v]) return;
                dis[v] = dis[u] + e.w;
                heap.push({dis[v], v});     // 注意：这里使用更新后的 dis
            });
        }
    }

    template <class _n_Array>
    void spfa(int st, _n_Array dis)
    {
        for (int i = 1; i <= n; ++ i) dis[i] = inf;
        bitset<N> inq; queue<node_t> hot;
        dis[st] = 0, hot.push({0, st});
        inq[st] = true;
        while (!hot.empty())
        {
            auto now = hot.front();
            hot.pop();
            const auto u = now.togo;
            inq[u] = false;     // 注意：SPFA 出队后需要取消标记
            forEach(u, [&](const edge &e)
            {
                const auto v = e.v;
                if (dis[u] + e.w >= dis[v]) return;
                dis[v] = dis[u] + e.w;
                if (inq[v]) return;
                inq[v] = true, hot.push({e.w, v});    // 注意：这里和 dij 不一样
            });
        }
    }
}

int dis[N][N];

template <class T>
const T &min(const T &a, const T &b, const T &c...)
{return std::min(a, min(b, c));}

#define DEBUG_ASSERT 0

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, k;
    scanner(n, m, k);
    FWS::init(n);
    using FWS::addEdge;
    int mm = m;
    vector<pair<int, int>> task, list;
    while (mm --)
    {
        int u, v, w;
        scanner(u, v, w);
        addEdge(u, v, w);
        addEdge(v, u, w);
        list.emplace_back(u, v);
    }
    while (k --) task.emplace_back
    (scanner.nextInt(), scanner.nextInt());
    memset(dis, 0x3f, sizeof dis);
    for (int i = 1; i <= n; ++ i)
        ShortestPath::dijkstra(i, dis[i]);
    int ans = inf;
#if DEBUG_ASSERT
    for (auto &ii : task)
        assert(dis[ii.first][ii.second] == dis[ii.second][ii.first]);
#endif
    for (auto [uu, vv] : list)
    {
        int tmp = 0;
        for (auto &ii : task)
            tmp += min(dis[ii.first][ii.second],
                       dis[ii.first][uu] + dis[vv][ii.second],
                       dis[ii.first][vv] + dis[uu][ii.second]);
        minimize(ans, tmp);
    }
    println(ans);

    return 0;
}

