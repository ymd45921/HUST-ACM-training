/**
 *
 * 网络流：板子没有锅，那重写次好了
 *
 * 因为节点数是 S + T + 7Days + nTasks，
 * 所以FWS初始化需要传入的 'n' = n + 9
 *
 * 网络流的题目debug是真的烦人==
 *
 * 离谱：重写一遍过（
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <bitset>

#define FN FlowNetwork

using namespace std;
using longs = long long;

const signed inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const int N = 1050, M = N * 8;

int n, e, c[N], sum;
bitset<8> a[N];

struct edge
{
    int u, v, next;
    longs w;
    edge() = default;
    edge(int u, int v, longs w, int next)
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

    void addedge(int u, int v, longs w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }
}

namespace FlowNetwork
{
    int dis[N], cur[N];
    int S, T, cnt = 0;

    const int __event = 9, __day = 2;
    auto event = [](int i){return __event+i;};
    auto day = [](int i){return __day+i;};

    auto __addedge = [](int u, int v, longs w)
    {
        FWS::addedge(u, v, w);
        FWS::addedge(v, u, 0);
    };

    auto __build = [](int t)
    {
        cnt = 0; FWS::init(n+9);
        S = ++ cnt; T = ++ cnt;
        for (int i = 1; i <= 7; ++ i)
            __addedge(S, ++ cnt, (t/7+(t%7>=i))*e);
        for (int i = 1; i <= n; ++ i)
        {
            __addedge(++ cnt, T, c[i]);
            for (int j = 1; j <= 7; ++ j)
                if (a[i][j]) __addedge(day(j), cnt, INF);
        }
    };

    bool bfs()
    {
        using namespace FWS;
        static queue<int> q;
        memset(dis, 0x3f, sizeof(int)*(cnt + 1));
        q.push(S); dis[S] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int cc = head[u]; ~cc; cc = ee[cc].next)
            {
                edge& e = ee[cc]; int v = e.v, w = e.w;
                cur[u] = head[u];
                if (!w || dis[v] <= dis[u] + 1) continue;
                dis[v] = dis[u] + 1; q.push(v);
            }
        }
        return dis[T] != inf;
    }

    longs dfs(int u, longs inflow)
    {
        using namespace FWS;
        if (u == T) return inflow;
        longs outflow = 0, rest = inflow;
        for (int &cc = cur[u]; ~cc; cc = ee[cc].next)
        {
            edge &e = ee[cc]; int v = e.v; longs w = e.w;
            edge &r = ee[cc ^ 1];
            if (!w || dis[v] != dis[u] + 1) continue;
            longs t = dfs(v, min(w, rest));
            outflow += t; e.w -= t; r.w += t; rest -= t;
            if (!rest) break;
        }
        if (!outflow) dis[u] = 0;
        return outflow;
    }

    longs dinic()
    {
        longs maxflow = 0;
        while (bfs()) maxflow += dfs(S, INF);
        return maxflow;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> e;
    int m, x; sum = 0;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> c[i] >> m;
        sum += c[i];
        while (m --)
        {
            cin >> x;
            a[i][x] = true;
        }
    }

    auto check = [&](int mid)
    {
        if (e * mid < sum) return false;        // 本题优化
        FN::__build(mid);
        return FN::dinic() == sum;
    };

    int ll = 0, rr = inf / e, ans = 0;          // 防止 mid*e > int
    while (ll <= rr)
    {
        int mm = ll + rr >> 1;
        if (check(mm)) ans = mm, rr = -- mm;
        else ll = ++ mm;
    }
    cout << ans << endl;

    return 0;
}