/**
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <array>
#include <algorithm>
#include <cstring>
#include <functional>
#include <queue>
#include <cassert>

#define USE_DINIC

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int X = 505;
using number = int;               // 设置流量数据类型
const int N = X * X * 3, M = N * 10;

struct edge
{
    int u, v, next;
    number w;
    edge() = default;
    edge(int u, int v, number w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    using method = function<void(const edge &e)>;

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    int addEdge(int u, int v, number w)
    {
        ee[tot] = {u, v, w, head[u]};
        return head[u] = tot ++;        // 返回加入的边的编号，方便处理重边
    }

    void forEach(int u, const method &iter)
    {
        for (auto ii = head[u];
             ii != -1;
             ii = ee[ii].next)
            iter(ee[ii]);
    }
}

namespace FN
{
    constexpr int inf = 0x3f3f3f3f;    // 严格匹配 number，不要自动转型！
    int S, T, total = 0;    // 重新建图之后的节点数

    int addEdge(int u, int v, number w)
    {
        auto pos = FWS::addEdge(u, v, w);
        FWS::addEdge(v, u, 0);
        return pos;
    }
#ifdef USE_DINIC
    /**
     * Dinic 算法
     * O (n²m)
     *
     * - 在残量网络上使用 BFS 构造分层图
     * - 在分层图上 DFS 寻找增广路，并更新边权
     * - 当前弧优化：避免寻找不可能增广的边
     */
    namespace Dinic
    {
        number dis[N];
        int cur[N]; // 当前弧优化

        // 先创建分层图
        bool bfs()
        {
            using namespace FWS;
            static queue<int> q;
            memset(dis, 0x3f, sizeof(number) * (total + 1));
            q.push(S); dis[S] = 0;
            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (int cc = head[u]; cc != -1; cc = ee[cc].next)
                {
                    edge& e = ee[cc];
                    int v = e.v; auto w = e.w;
                    cur[u] = head[u];
                    if (!w || dis[v] <= dis[u] + 1) continue;
                    dis[v] = dis[u] + 1; q.push(v);
                }
            }
            return dis[T] != inf;
        }

        number dfs(int u, number inflow)
        {
            using namespace FWS;
            if (u == T) return inflow;
            number outflow = 0, rest = inflow;
            for (int &cc = cur[u]; cc != -1; cc = ee[cc].next)  // 当前弧优化
            {
                edge &e = ee[cc], &r = ee[uint(cc) ^ 1u];
                int v = e.v; auto w = e.w;
                if (!w || dis[v] != dis[u] + 1) continue;
                int t = dfs(v, min(w, rest));
                outflow += t; e.w -= t; r.w += t; rest -= t;
                if (!rest) break;
            }
            if (!outflow) dis[u] = 0;
            return outflow;
        }

        number go()
        {
            number maxFlow = 0;
            while (bfs()) maxFlow += dfs(S, inf);
            return maxFlow;
        }
    }
#elif defined USE_ISAP
    /**
     * Improved Shortest Augumenting Path
     * O (n²m)，比起 Dinic 算法只需要一次 BFS
     *
     * - 反向 BFS 并标记节点深度
     * - 正向 DFS，用尽节点的出流时回溯加深深度
     * - gap 优化：当某一深度不再包含节点时停止搜索
     * - 当 S 的深度达到 n 时，搜索一定结束
     *
     * 和 Dinic 类似，本算法也可以进行当前弧优化
     */
    namespace ISAP
    {
        int dep[N], gap[N]; // 节点的深度 & 特定深度节点的数量
        number maxFlow = 0;
        int cur[N];         // 当前弧优化

        void bfs()
        {
            memset(dep, -1, sizeof dep);
            memset(gap, 0, sizeof gap);
            dep[T] = 0, gap[0] = 1;
            queue<int> q; q.push(T);
            using namespace FWS;
            while (!q.empty())
            {
                auto u = q.front();
                q.pop();
                for (int cc = head[u]; cc != -1; cc = ee[cc].next)
                {
                    edge& e = ee[cc]; int v = e.v;
                    if (dep[v] != -1) continue;
                    q.push(v);
                    ++ gap[dep[v] = dep[u] + 1];
                }
            }
        }

        number dfs(int u, number flow)
        {
            if (u == T) return maxFlow += flow, flow;
            number used = 0;
            using namespace FWS;
            for (int cc = head[u]; cc != -1; cc = ee[cc].next)
            {
                edge& e = ee[cc], &r = ee[uint(cc) ^ 1u];
                int v = e.v; auto w = e.w;
                if (!w || dep[v] + 1 != dep[u]) continue;
                auto t = dfs(v, min(w, flow - used));
                if (t) e.w -= t, r.w += t, used += t;
                if (used == flow) return used;
            }
            if (-- gap[dep[u]] == 0) dep[S] = total + 1;
            ++ gap[++ dep[u]];
            return used;
        }

        number go()
        {
            maxFlow = 0;
            bfs();
            while (dep[S] < total)
                memcpy(cur, FWS::head, sizeof(int) * (total + 1)),  // 当前弧优化
                        dfs(S, inf);
            return maxFlow;
        }
    }
#endif

    void setInfo(int s, int t, int cnt)
    {FN::S = s, FN::T = t, FN::total = cnt;}
}

string s[505];
bitset<505> ty;
array<bitset<X>, X> e;

auto buildGraph(int n)
{
    FWS::init();
    using namespace FN;
    S = T = total = n;
    S = ++ total, T = ++ total;
    for (int i = 1; i <= n; ++ i)
        if (ty[i]) addEdge(S, i, 1);
        else addEdge(i, T, 1);
    for (int i = 1; i <= n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
            if (e[i][j])
            {
                if (ty[i]) addEdge(i, j, 1);
                else addEdge(j, i, 1);
            }
}

bitset<X> vis;

void dfs(int u, int n)
{
    vis[u] = true;
    for (int i = 1; i <= n; ++ i)
        if (e[u][i] && !vis[i])
        {
            ty[i] = !ty[u];
            dfs(i, n);
        }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> s[i];
    auto siz = s[1].length();
    for (int i = 1; i < n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
        {
            auto diff = 0;
            for (int k = 0; k < siz; ++ k)
                if (s[i][k] != s[j][k]) ++ diff;
            if (diff == 2)
                e[i][j] = e[j][i] = true;
        }
    for (int i = 1; i <= n; ++ i)
        if (!vis[i]) dfs(i, n);
    buildGraph(n);
    auto ans = FN::Dinic::go();
    ans = n - ans;
    cout << ans << endl;

    return 0;
}

