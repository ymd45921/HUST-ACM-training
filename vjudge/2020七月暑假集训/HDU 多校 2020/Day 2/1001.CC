/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const uint N = 1e5 + 5, M = N << 1u;
pair<uint, int> city[N];
int b[N];
bitset<N> done;

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
    edge ee[M*2];

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

namespace UFS
{
    using number = int;
    number p[N];

    void init(int n = N)
    {
        for (int i = 0; i < n; ++ i)
            p[i] = i;
    }

    number father(int x)
    {
        return p[x] == x ? x : p[x] = father(p[x]);
    }

    number join(int x, int y)
    {
        return p[father(x)] = p[father(y)];
    }
}

longs ans = 0;

void dfs(int u)
{
    using namespace FWS;
    using namespace UFS;
    for (int c = head[u]; ~c; c = ee[c].next)
    {
        auto v = ee[c].v;
        if (father(v) == father(u) ||
            b[father(v)] > b[father(u)]) continue;
        else if (b[father(v)] == b[father(u)]) join(u, v);
        else
        {
            ans += b[father(u)] - b[father(v)];
            join(u, v); dfs(v);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, m;
    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        FWS::init(n);
        UFS::init(n + 1);
        for (int i = 1; i <= n; ++ i)
            cin >> b[i], city[i] = {b[i], i};
        ans = 0; done.reset();
        while (m --)
        {
            int u, v;
            cin >> u >> v;
            FWS::addEdge(u, v, 0);
        }
        sort(city + 1, city + 1 + n);
        for (int ii = n; ii > 0; -- ii) dfs(ii);
        for (int i = 1; i <= n; ++ i)
            if (!done[UFS::father(i)])
                ans += b[UFS::father(i)], done[UFS::father(i)] = true;
        cout << ans << endl;
    }

    return 0;
}