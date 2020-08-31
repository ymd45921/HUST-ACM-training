/**
 *
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int N = 2e5 + 5;

#define CONTINUE return true
#define BREAK return false
#define RETURN return true

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
    edge ee[N*2];

    void init(int n)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addedge(int u, int v, int w = 0)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
        ee[tot] = edge(v,u,w,head[v]);
        head[v] = tot ++;
    }

    void foreach(int st, const function<bool(edge&)>& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            if (!func(ee[c])) break;
    }
}

int a[N], d[N];
vector<int> vv[N];

void dfs(int u, int p, int dd)
{
    using namespace FWS;
    d[u] = dd ++;
    foreach(u, [&](edge& e)
    {
        if (e.v == p) CONTINUE;
        dfs(e.v, u, dd);
        RETURN;
    });
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, e, u, v;
    cin >> n >> e;
    FWS::init(n);
    for (int i = 1; i <= n; ++ i)
        cin >> a[i];
    for (int i = 1; i < n; ++ i)
    {
        cin >> u >> v;
        FWS::addedge(u,v);
    }


    return 0;
}