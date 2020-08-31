#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;
struct edge
{
    int u, v, next;

};

const int mod = 1e9 + 7;
const int N = 3e5 + 5;

namespace FWS
{
    int head[N];
    edge e[N<<1];
    int tot;

    inline void init(int n)
    {
        tot = 0;
        memset(head, -1, sizeof(int)*(n+1));
    }

    inline void addedge(int u, int v)
    {
        e[++tot] = {u,v,head[u]};
        head[u] = tot;
        e[++tot] = {v,u,head[v]};
        head[v] = tot;
    }

}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t, n, m, k;
    int u, v;
    cin >> t;
    while (t --)
    {
        cin >> n >> m >> k;
        FWS::init(n);
        for (int i = 1; i < n; ++ i)
        {
            cin >> u >> v;
            FWS::addedge(u,v);
        }
        for (int i = 0; i < m; ++ i)
        {
            
        }
    }


    return 0;
}