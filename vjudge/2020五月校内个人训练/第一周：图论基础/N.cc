/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 8005, M = 20005;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N * 2];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot++;
        ee[tot] = edge(v, u, w, head[v]);
        head[v] = tot++;
    }
}

namespace toSAT
{
    using namespace FWS;

    int n;
    unsigned dfn[N * 2], cnt;
    bool mark[N * 2];           // visit 数组

    void init(int _n)
    {
        n = _n; _n *= 2;
        FWS::init(_n);
        memset(mark, 0, sizeof(bool)*(_n));
    }

    bool dfs(unsigned u)
    {
        if (mark[u ^ 1]) return false;
        else if (mark[u]) return true;
        mark[u] = true;
        dfn[cnt ++] = u;
        for (int c = head[u]; ~c; c = ee[c].next)
            if (!dfs(ee[c].v)) return false;
        return true;
    }

    bool solve()
    {
        auto lim = n * 2;
        for (int i = 0; i < lim; i += 2)
            if (!mark[i] && !mark[i ^ 1])
            {
                cnt = 0; if (!dfs(i))
                {
                    while (cnt) mark[dfn[-- cnt]] = false;
                    if (!dfs(i + 1)) return false;
                }
            }
        return true;
    }

    void addClause(int u, int v)
    {
        FWS::addedge(u, v ^ 1, 0);
        FWS::addedge(v, u ^ 1, 0);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, m, a, b;
    while (cin >> n >> m)
    {
        toSAT::init(n);
        for (int i = 0; i < m; ++ i)
        {
            cin >> a >> b;
            toSAT::addClause(-- a, -- b);
        }
        if (toSAT::solve())
            for (int i = 0; i < n * 2; ++ i)
                if (toSAT::mark[i]) cout << i + 1 << endl;
                else continue;
        else cout << "NIE" << endl;
    }

    return 0;
}