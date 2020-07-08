/**
 *
 * 树的直径也不是一个新概念了：
 * - 可以双 DFS 法求出
 * - 可以树形 DP 求出
 *
 * 树的直径有着这样的一些特性：
 * - 树上最长的路径
 * - 任意节点距离最远的节点一定是直径的端点
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
using longs = long long;
using uint = unsigned;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 2e5 + 5, M = N;

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

    void addEdge(int u, int v, int w)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
        ee[tot] = edge(v, u, w, head[v]);
        head[v] = tot ++;
    }
}

namespace TreeDia
{
    uint dis[N];
    auto cleanDis = []{memset(dis, -1, sizeof(dis));};
    struct {int st, ed;} ep;

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
        return ep = {st, ed};
    }
}

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

namespace solution
{
    vector<pair<int, int>> ans;
    bool open[N];
    uint father[N];
    longs cnt = 0;

    using namespace FWS;
    using TreeDia::dis;
    using TreeDia::ep;

    void dfs$1(int u)
    {
        for (int c = head[u]; ~c; c = ee[c].next)
            if (dis[ee[c].v] > dis[u])
            {
                father[ee[c].v] = u;
                dfs$1(ee[c].v);
                open[u] |= open[ee[c].v];
            }
    }

    void dfs$2(int u, int root)
    {
        for (int c = head[u]; ~c; c = ee[c].next)
            if (dis[ee[c].v] > dis[u])
                dfs$2(ee[c].v,
                      open[ee[c].v] ? ee[c].v : root);
        if (!open[u])
            if (dis[u] > dis[u] + dis[ep.ed] - dis[root] * 2)
                cnt += dis[u], ans.emplace_back(ep.st, u);
            else cnt += dis[u] + dis[ep.ed] - dis[root] * 2,
                ans.emplace_back(ep.ed, u);
        else return;
    }

    auto solve()
    {
        open[ep.ed] = true;
        dfs$1(ep.st), dfs$2(ep.st, ep.st);
        for (auto u = ep.st, v = ep.ed; u != v; v = father[v])
            cnt += dis[v], ans.emplace_back(u, v);
        // return make_pair(cnt, ans); // make_pair 复制整个 vector 得到新的
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, a, b, m;
    cin >> n; m = n;
    FWS::init(n);
    while (-- m)
    {
        cin >> a >> b;
        FWS::addEdge(a, b, 1);
    }
    TreeDia::$duoDFS(n);
    solution::solve();
    cout << solution::cnt << endl;
    for (auto & ii : solution::ans)
        cout << ii.first << ' '
            << ii.second << ' '
            << ii.second << endl;

    return 0;
}