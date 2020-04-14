/**
 *
 * 暴力会超时
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

const int N = 8e5;
int n, q, hit[N];

struct edge
{
    int u, v;
    int next;

    edge() = default;
    edge(int s, int t, int next)
            : u(s) , v(t) , next(next) {}
};

namespace FWS
{
    int tot = 0;
    edge ee[N << 1];
    int head[N];

    void init()
    {
        tot = 0;
        memset(head,-1,sizeof head);
    }

    void addedge(int u, int v)
    {
        ee[tot] = edge(u, v, head[u]);     // 偶数正向边
        head[u] = tot ++;
        ee[tot] = edge(v, u, head[v]);
        head[v] = tot ++;
    }
}

int attack(int u, int father, int dis)
{
    ++ hit[u];
    using namespace FWS;
    if (dis)
        for (int c = head[u]; ~c; c = ee[c].next)
        {
            edge& e = ee[c];
            if (e.v == father) continue;
            attack(e.v, e.u, dis - 1);
        }
    return hit[u];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    FWS::init();

    int u, v;
    cin >> n >> q;
    for (int i = 1; i < n; ++ i)
    {
        cin >> u >> v;
        FWS::addedge(u, v);
    }
    while (q --)
    {
        cin >> u;
        cout << attack(u, 0, 2) << endl;
    }


    return 0;
}