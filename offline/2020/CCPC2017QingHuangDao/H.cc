/**
 *
 *
 */
#include <bits/stdc++.h>

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
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int X = 3e3 + 5, A = 1e6 + 5;
const int N = X, M = N * N + N;        // 设置点、边数限制
using number = int;               // 设置流量数据类型

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
    constexpr number inf = 0x3f3f3f3f;    // 严格匹配 number，不要自动转型！
    int S, T, total = 0;    // 重新建图之后的节点数

    int addEdge(int u, int v, number w)
    {
        auto pos = FWS::addEdge(u, v, w);
        FWS::addEdge(v, u, 0);
        return pos;
    }

    void addEdgeX(int u, int v)
    {
        FWS::addEdge(u, v, 1);
        FWS::addEdge(v, u, 1);
    }

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
                assert(e.u == r.v && e.v == r.u);
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
}

bitset<N> &depart(int n)
{
    static bitset<N> ty;
    bitset<N> vis;
    static function<void(int, bool)> dfs = [&](int u, bool now)
    {
        vis[u] = true, ty[u] = now;
        FWS::forEach(u, [&](const edge &e)
        {
            auto v = e.v;
            if (!vis[v]) dfs(v, !now);
        });
    };
    for (int i = 1; i <= n; ++ i)
        if (!vis[i]) dfs(i, true);
    return ty;    
}

// 建图函数
template <int siz>
void buildGraph(int n, int k, bitset<siz> &isPrime)
{
    using namespace FN;
    S = n + 1, T = total = n + 2;
    int SS = ++ total;
    for (int i = 1; i < n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
            if (isPrime[i + j]) addEdgeX(i, j);
    const auto &ty = depart(n);
    addEdge(S, SS, k);
    for (int i = 1; i <= n; ++ i)
        if (ty[i]) addEdge(SS, i, 1);
        else addEdge(i, T, 1);
}

template <int n> bitset<n> &EulerSieve()
{
    static vector<int> prime;
    static bitset<n> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime.push_back(i);
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = true;
            if (i % pp == 0) break;
        }
    }
    return vis;
}

int a[X];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = nextInt(), n, k;
    using In::read;
    auto &isPrime = EulerSieve<A * 2>();
    while (t --)
    {
        read(n, k);
        for (int i = 1; i <= n; ++ i)
            read(a[i]);
        
    }


    return 0;
}

