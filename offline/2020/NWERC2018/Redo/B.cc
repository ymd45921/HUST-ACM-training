/**
 *
 * 一眼拓扑排序 + DAG
 * 看似没有特定的解法，但是又很多种做法
 * 
 * 题目的要求：
 * - 对于每一个特定的任务，必须发生在它的依赖之后
 * - 对于前面发生的任何任务，将造成当前任务额外的花销
 * 
 * 这个题目最简单的做法其实并没有那么花里胡哨：
 * - 首先使用 DFS 标记
 * - 然后拓扑排序，对于每一层优先使用大的
 * 
 * 但是真的好多拓扑排序的问题都是倒着来啊（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>
#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128
#define heap priority_queue

template<class T>
inline T nexT()
{
    T x = 0; int f = 0, ch = getchar();
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

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 4e5 + 5, M = N;
int e[N];
const int INF = 0x3f3f3f3f;

namespace FWS
{
    int head[N], in[N], out[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(in, 0, sizeof(int) * (n + 1));
        memset(out, 0, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
        ++ out[u], ++ in[v];
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u]; 
            c != -1; 
            c = ee[c].next)
            process(ee[c]);
    }
}

namespace TopoSort
{
    bitset<N> vis;
    int deg[N], rank[N];
    using namespace FWS;

    struct copmarer
    {
        bool operator()(int i, int j)
        {return rank[i] < rank[j];}
    };

    void init(int n = N - 1)
    {
        memcpy(deg, in, sizeof(int) * (n + 1));
        vis.reset();
        memset(rank, 0, sizeof(int) * (n + 1));
    }

    void dfs(int u)
    {
        vis[u] = true;
        rank[u] = e[u];                 // 表示这条线路后面的路径的预期
        forEach(u, [&](const edge &e)
        {
            const auto v = e.v;
            if (!vis[v]) dfs(v);
            rank[u] = max(rank[u], rank[v] + 1);
        });
    }

    int run(int n)
    {
        init(n);
        for (int i = 1; i <= n; ++ i)
            if (!vis[i]) dfs(i);
        heap<int, vector<int>, copmarer> q;
        for (int i = 1; i <= n; ++ i)
            if (!deg[i]) q.push(i);
        int ans = 0, cnt = 0;    
        while (!q.empty())   
        {
            int u = q.top(); q.pop();
            ans = max(ans, cnt + rank[u]);  // 更大的路径优先靠前出队
            forEach(u, [&](const edge& e)
            {if (!-- deg[e.v]) q.push(e.v);});
            ++ cnt;
        }
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    using In::read;
    int d, u, n;
    read(n), FWS::init(n);
    for (int v = 1; v <= n; ++ v)
    {
        read(e[v], d);
        while (d --)
        {
            read(u);
            FWS::addEdge(u, v);
        }
    }
    auto ans = TopoSort::run(n);
    printf("%d\n", ans);

    return 0;
}

