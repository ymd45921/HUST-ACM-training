/**
 * 
 * 有趣的题目：
 * 可以通过反向跑边来贪心
 * 
 * luogu 上还有使用 dijkstra 的神秘做法
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 5e5 + 5, M = N;
const int INF = 0x3f3f3f3f;

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
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    inline void forEach(int st, const function<void(edge&)>& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            func(ee[c]);
    }
}

int color[N], dis[N];
bitset<N> vis;

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt(), m = nextInt();
    FWS::init(n);
    memset(color, -1, sizeof color);
    memset(dis, -1, sizeof dis);
    while (m --)
    {
        int u = nextInt(),
            v = nextInt(),
            t = nextInt();
        FWS::addEdge(v, u, t);
    }
    queue<int> que;
    que.push(n); dis[n] = 0;
    while (!que.empty())
    {
        auto top = que.front();
        que.pop();
        FWS::forEach(top, [&](edge &e)
        {
            if (vis[e.v]) return;
            if (color[e.v] == e.w)
            {
                que.push(e.v);
                vis[e.v] = true;
                dis[e.v] = max(dis[e.v], dis[e.u] + 1);
            }
            else color[e.v] = !e.w;
        });
    }
    printf("%d\n", dis[1]);
    // for (int i = 1; i <= n; ++ i)
    //     printf("%d ", color[i]);
    for (int i = 1; i <= n; ++ i)
        printf(color[i] ? "1" : "0");
    puts("");   

    return 0;
}
