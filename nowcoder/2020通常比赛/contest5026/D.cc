/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
typedef long long longs;
typedef long double longd;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
        : u(u), v(v), w(w), next(next) {}
};

const int N = 1e5+5, M = 2e5+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int n, m;

namespace FWS
{
    int head[N];
    int tail[N];
    int tot;
    edge ee[M*2];

    void init()
    {
        memset(head, -1, sizeof(int)*(n+1));
        memset(tail, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
        ee[tot] = edge(v,u,w,tail[v]);
        tail[v] = tot ++;
    }
}

namespace dij
{
    using namespace FWS;

    bool vis[N];
    longs ds[N], dt[N];

    void dijkstra(int goal)
    {
        priority_queue<pair<longs ,int>> q;
        int* li = goal == n ? tail : head;
        longs* dis = goal == n ? dt : ds;

        q.push(make_pair(0, goal));
        memset(vis,0, sizeof(bool)*(n+1));
        memset(dis,0x3f, sizeof(longs)*(n+1));
        dis[goal] = 0;
        while (!q.empty())
        {
            int u = q.top().second; q.pop();
            if (vis[u]) continue; vis[u] = true;
            for (int c = li[u]; ~c; c = ee[c].next)
            {
                edge& e = ee[c];
                int v = e.v;
                if (dis[v] >= dis[u] + e.w)
                    q.push(make_pair(
                            -(dis[v] = dis[u] + e.w),
                            v
                    ));
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    using dij::dijkstra;

    int u, v, c;
    int x, q;

    cin >> n >> m;
    FWS::init();
    while (m --)
    {
        cin >> u >> v >> c;
        FWS::addedge(u,v,c);
    }
    dijkstra(1); dijkstra(n);
    const longs shortest = dij::ds[n];

    cin >> q;
    while (q --)
    {
        cin >> x;
        auto& ii = FWS::ee[(x-1)<<1];
        longs to = dij::ds[ii.v] + dij::dt[ii.u] + ii.w;
        if (to < shortest) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}