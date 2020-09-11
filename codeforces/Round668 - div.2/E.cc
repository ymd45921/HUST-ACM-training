/**
 *
 * 这竟然考了树的直径
 *
 * 因为想要不被抓到，最好还是要在最长链上，所以求树的直径
 * 简  单  的  追  及  问  题
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 1e5 + 5, M = N;
const int INF = 0x3f3f3f3f;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M*2];

    void init(int n = N-1)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addEdge(int u, int v, int w)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    void addBiEdge(int u, int v, int w)
    {
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    inline void forEach(int st, const function<void(edge&)>& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            func(ee[c]);
    }
}

namespace TreeDia
{
    uint dis[N];
    auto cleanDis = []{memset(dis, -1, sizeof(dis));};
    struct {int st, ed, dia;} ep;

    void dfs(int u)
    {
        using namespace FWS;
        for (int c = head[u]; ~c; c = ee[c].next)
            if (!~dis[ee[c].v])
                dis[ee[c].v] = dis[u] + 1,
                        dfs(ee[c].v);
    }

    auto $duoDFS(int n)
    {
        cleanDis();
        dis[1] = 0, dfs(1);
        int st = 1;
        for (int i = 2; i <= n; ++ i)
            if (dis[i] > dis[st]) st = i;
        cleanDis();
        dis[st] = 0, dfs(st);
        int ed = st;
        for (int i = 1; i <= n; ++ i)
            if (dis[i] > dis[ed]) ed = i;
        return ep = {st, ed, static_cast<int>(dis[ed])};
    }
}

int dis[N];
bitset<N> vis;

int bfs(int u, int v)
{
    queue<int> q;
    memset(dis, -1, sizeof dis);
    dis[u] = 0, q.push(u), vis.reset();
    vis[u] = true;
    while (!q.empty())
    {
        auto top = q.front();
        q.pop();
        FWS::forEach(top, [&](edge &e)
        {
            if (vis[e.v]) return;
            q.push(e.v);
            dis[e.v] = dis[e.u] + 1;
            vis[e.v] = true;
        });
        if (dis[v] >= 0) return dis[v];
    }
    return dis[v];
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(),
            a = nextInt(),
            b = nextInt(),
            da = nextInt(),
            db = nextInt();
        FWS::init(n);
        for (int i = 1; i < n; ++ i)
        {
            int u = nextInt(), v = nextInt();
            FWS::addBiEdge(u, v, 0);
        }
        auto dia = TreeDia::$duoDFS(n).dia;
        auto dist = bfs(a, b);
        bool ok = da * 2 < dia && db > 2 * da && dist > da;
        cout << (ok ? "Bob" : "Alice") << endl;
    }

    return 0;
}

