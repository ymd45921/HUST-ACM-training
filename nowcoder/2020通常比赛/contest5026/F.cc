/**
 *
 * 带边权的LCA + 最短路
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <cstring>
#include <functional>

#define uu second
#define aa first

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

const int N = 1e5+5, M = N;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int n, m;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[N];

    void init()
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }

    inline void foreach(int st, function<void(edge&)>& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            func(ee[c]);
    }

    inline void foreach(int st, function<void(edge&)>&& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            func(ee[c]);
    }
}

namespace LCA
{
    int lg2[N], deep[N];
    int father[30][N*2];

    void init()
    {
        lg2[0] = -1;
        memset(deep, 0, sizeof(int)*(n+1));
    }

    inline void dfs(int thispoint,int thisfather)
    {
        deep[thispoint] = deep[thisfather]+1;
        father[0][thispoint] = thisfather;
        for(int i=1;i<=lg2[deep[thispoint]];++i)
            father[i][thispoint] = father[i-1][father[i-1][thispoint]];
        FWS::foreach(thispoint, [&](edge& ii) -> void {
            if(ii.v != thisfather) dfs(ii.v,thispoint);
        });

    }

    inline void preLca(int s)
    {
        for(int i=1;i<=n;++i)           // 常数优化计算log2对数
            lg2[i] = lg2[i-1]+(1<<lg2[i-1]==i);
        dfs(s,0);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int u, v, w, x, y, o;
    cin >> n >> m;
    set<pair<int,int>> ss;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> x;
        ss.insert(make_pair(x,i));
    }
    for (int i = 1; i < n; ++ i)
    {
        cin >> u >> v >> w;
        FWS::addedge(u,v,w);
    }

    while (m --)
    {
        cin >> o;
        if (o & 1)
        {
            cin >> u >> x;
            ss.insert(make_pair(x,u));
        }
        else
        {
            cin >> u >> x >> y;
            auto st = ss.lower_bound(make_pair(x,0));
            auto ed = ss.upper_bound(make_pair(y,0));
        }
    }


    return 0;
}