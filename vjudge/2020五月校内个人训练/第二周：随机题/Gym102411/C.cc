/**
 *
 * 十字绣，怎么还 RE，懂了傻逼了（
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 105, M = N * N * 4;
char map[N][N];
int id[N][N], cnt = 0, vis[M];
vector<int> ans;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N * N];
    int tot;
    edge ee[M * 2];

    void init(int n)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addEdge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }
}

void init(int n, int m)
{
    ans.clear(); cnt = 0;
    for (int i = 0; i <= n; ++ i)
        for (int j = 0; j <= m; ++ j)
            id[i][j] = cnt ++;
    FWS::init(cnt + 5);
}

void addEdge(int u, int v, int color)
{
    FWS::addEdge(u, v, color);
    FWS::addEdge(v, u, color);
}

void dfs(int u, int last_color)
{
    using namespace FWS;
    for (auto cc = head[u]; cc + 1; cc = ee[cc].next)
    {
        if (vis[cc / 2] || ee[cc].w == last_color) continue;
        vis[cc / 2] = true;
        dfs(ee[cc].v, ee[cc].w);
        ans.push_back(ee[cc].v);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int m, n;
    cin >> m >> n;
    init(n, m); int sp, div = m + 1;
    for (int i = 1; i <= n; ++ i) cin >> (map[i] + 1);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            if (map[i][j] == 'X') sp = id[i][j],
                addEdge(id[i - 1][j - 1], id[i][j], 1),
                addEdge(id[i - 1][j], id[i][j - 1], 1),
                addEdge(id[i - 1][j], id[i][j], 0),
                addEdge(id[i - 1][j - 1], id[i][j - 1], 0);
    dfs(sp, 1);
    cout << (ans.size() - 1) << endl;
    for (auto & ii : ans) cout << ii % div << ' ' << ii / div << endl;

    return 0;
}