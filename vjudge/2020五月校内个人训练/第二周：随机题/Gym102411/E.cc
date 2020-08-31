/**
 *
 * 啊这，真nm就暴力呗
 * 说是暴力也不是从每一个点起步搜索
 *
 * 因为这个要求很强，很多情况都可以被剪枝：
 * 很多时候需要重置 visit 的时候说明已经不行了（吗？）
 * 注意边界情况特判；
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 2e5 + 5, M = N;
int n, m, c[N];

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N-1)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addEdge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
        ee[tot] = edge(v,u,w,head[v]);
        head[v] = tot ++;
    }
}

int BFS()
{
    if (n == 1) return 1;
    queue<int> q;
    int visit[N] {0}, depth[N] {0};
    bool used[N] {false};
    for (int i = 1; i <= m; ++ i)
    {
        q.push(c[i]);
        visit[c[i]] = 1;
        depth[c[i]] = 1;
        used[c[i]] = true;
    }
    int found = -1;
    using namespace FWS;
    while (!q.empty())
    {
        auto top = q.front(); q.pop();
        for (auto ii = head[top]; ~ii; ii = ee[ii].next)
        {
            auto &e = ee[ii];
            if (!depth[e.v] || depth[e.v] == depth[e.u] + e.w)
            {
                visit[e.v] += visit[e.u];
                depth[e.v] = depth[e.u] + e.w;
                if (visit[e.v] == m)
                {found = e.v; break;}
                if (!used[e.v])
                {
                    q.push(e.v);
                    used[e.v] = true;
                }
            }
        }
        if (found > 0) break;
    }
    return found;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n >> m;
    int u, v;
    FWS::init(n);
    for (int i = 1; i < n; ++ i)
    {
        cin >> u >> v;
        FWS::addEdge(u, v, 1);
    }
    for (int i = 1; i <= m; ++ i)
        cin >> c[i];
    int found = BFS();
    if (found < 0) cout << "NO" << endl;
    else cout << "YES" << endl << found << endl;

    return 0;
}