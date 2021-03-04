/**
 *
 * 这个题也算是读了个假题（）
 * 
 * 假题++ 原来移动到的节点未必是相邻节点啊——
 * 因为祖先和后代本来就不只是直系祖先和直系后代啊
 * 草，淦恁娘==
 * 
 * 依然是一个完美匹配的问题——但是不是相邻的
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

static class 
{
    template<class T>
    inline static T nexT()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:
    static int nextInt(){return nexT<int>();}
    static longs nextLongs() {return nexT<longs>();}
    static lll nextInt128() {return nexT<lll>();} 
} Scanner;

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

const int N = 1e5 + 5, M = N;
const int INF = 0x3f3f3f3f;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
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

bitset<N> vis;  // 未完全匹配标记
int dp[N];      // 表示子树需要的祖先匹配数量

void dfs(int u, int fa)
{
    bool flag = false;
    dp[u] = -1;
    FWS::forEach(u, [&](const edge &e)
    {
        if (e.v == fa) return;
        const auto v = e.v;
        dfs(v, u);
        if (vis[v]) flag = true;
        dp[u] += max(dp[v], (int)vis[v]);
    });
    if (!flag || dp[u] > 0) vis[u] = true;
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
    
    int n = Scanner.nextInt();
    FWS::init(n);
    for (int i = 1; i < n; ++ i)
    {
        int u = Scanner.nextInt(), 
            v = Scanner.nextInt();
        FWS::addEdge(u, v);
        FWS::addEdge(v, u);    
    }
    dfs(1, 0);
    puts(dp[1] ? "Alice" : "Bob");

    return 0;
}

