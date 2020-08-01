/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <bitset>

#define LEFT(x) (x)
#define RIGHT(x) (x + n)

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

struct edge
{
    int u, v, next;
    longs w;
    edge() = default;
    edge(int u, int v, longs w, int next)
            : u(u), v(v), w(w), next(next) {}
};

constexpr int N = 2e5 + 5, M = N * 3;
constexpr longs inf = 0x3f3f3f3f3f3f3f3f;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M*2];

    using method = function<void(const edge &)>;

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 0)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    void addBiEdge(int u, int v, int w = 0)
    {
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    void forEach(int u, const method &iter)
    {
        for (auto ii = head[u];
             ii != -1;
             ii = ee[ii].next)
            iter(ee[ii]);
    }
}

char type[N];
longs dis[N];
bitset<N> visit;

inline void dijkstra(int s, int n)
{
    visit.reset();
    memset(dis, 0x3f, sizeof(longs) * (2 * n + 1));
    using node = pair<longs, int>;
    dis[s] = 0;
    int visited = 0;
    priority_queue<node, vector<node>, greater<node>> heap;
    heap.push({0, s});
    while(!heap.empty())
    {
        auto top = heap.top();
        auto u = top.second;
        heap.pop();
        if(visit[u]) continue;
        visit[u] = true;
        ++ visited;
        FWS::forEach(u, [&](const edge &i)
        {
            if(dis[u] + i.w < dis[i.v])
            {
                dis[i.v] = dis[u] + i.w;
                heap.push({dis[i.v], i.v});
            }
        });
    }
}

int main()
{
    int cases = nextInt(), n, m, s, t, x;
    while (cases --)
    {
        n = nextInt(), m = nextInt(), s = nextInt();
        t = nextInt(), x = nextInt();
        scanf("%s", type + 1);
        FWS::init(n * 2);
        for (int i = 1; i <= n; ++ i) FWS::addBiEdge(i, i + n, x);
        while (m --)
        {
            int u = nextInt(), v = nextInt(), w = nextInt();
            if (type[v] == 'R' || type[v] == 'M')
                FWS::addBiEdge(RIGHT(u), RIGHT(v), w);
            if (type[v] == 'L' || type[v] == 'M')
                FWS::addBiEdge(LEFT(u), LEFT(v), w);
        }
        longs ans = inf;
        if (type[s] == 'L' || type[s] == 'M')
        {
            dijkstra(LEFT(s), n);
            if (type[t] == 'L' || type[t] == 'M')
                ans = min(ans, dis[LEFT(t)]);
            if (type[t] == 'R' || type[t] == 'M')
                ans = min(ans, dis[RIGHT(t)]);
        }
        if (type[s] == 'R' || type[s] == 'M')
        {
            dijkstra(RIGHT(s), n);
            if (type[t] == 'L' || type[t] == 'M')
                ans = min(ans, dis[LEFT(t)]);
            if (type[t] == 'R' || type[t] == 'M')
                ans = min(ans, dis[RIGHT(t)]);
        }
        cout << ans << endl;
    }

    return 0;
}