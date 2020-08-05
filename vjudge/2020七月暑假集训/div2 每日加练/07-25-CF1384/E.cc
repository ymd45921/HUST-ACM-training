/**
 *
 * 删除了必须按照顺序调整字符的限制
 * 等于说废掉了上一个题做法中的弱连通分量的拓扑有序性
 * 而且因为任意连边，还有可能出现环
 *
 * 一些知识：
 * __builtin_popcount：计算 32 bit 中有多少个位为 1
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <functional>
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

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 30, M = 1e5 + 5;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M*2];

    using method = function<void(const edge &e)>;

    void init(int n = N-1)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 0)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    void addBiEdge(int u, int v, int w = 0)
    {
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    void forEach(int u, const method &iter)
    {
        for (auto ii = head[u];
             ii != -1;
             ii = ee[ii].next)
            iter(ee[ii]);
    }
}

constexpr auto alp = 20u;
constexpr auto dict = 1u << alp;
bitset<alp> x;
bitset<dict> dp;
uint reach[N];

void init()
{
    FWS::init(alp);
    x.reset();
    dp.reset();
    memset(reach, 0, sizeof(reach));
}

void DFS(int u)
{
    x[u] = true;
    FWS::forEach(u, [&](auto e)
    { if (!x[e.v]) DFS(e.v); });
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n;
    string a, b;

    cin >> t;
    while (t --)
    {
        cin >> n >> a >> b;
        init();
        for (int i = 0; i < n; ++ i)
            if (a[i] != b[i])
            {
                FWS::addBiEdge(a[i] - 'a', b[i] - 'a');
                reach[a[i] - 'a'] |= 1u << uint(b[i] - 'a');
            }
        auto cnt = 0, ans = 0;
        for (int i = 0; i < alp; ++ i)
            if (!x[i]) DFS(i), ++ cnt;
        dp[0] = true;
        for (uint msk = 0; msk < dict; ++ msk)
            if (dp[msk])
            {
                ans = max(ans, __builtin_popcount(msk));
                for (uint u = 0; u < alp; ++ u)
                    if ((~msk >> u & 1u) && !(reach[u] & msk))
                        dp[msk | 1u << u] = true;
            }
        auto step = 2 * alp - cnt - ans;
        cout << step << endl;
    }

    return 0;
}