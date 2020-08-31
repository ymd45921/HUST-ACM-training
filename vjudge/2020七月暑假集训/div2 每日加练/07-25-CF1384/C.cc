/**
 *
 * 注意，选择的位置未必是连续的，只要是相同的字母就可以
 *
 * 那样的话确实可以建一个图，将所有可以中转的边全部中转
 * 当然因为实际上数据量和复杂度没什么关系，所以也可以使用乱搞一些的办法（set
 *
 * 比较直观的说法：
 * - 转变时，所有需要改动的值都直接转变为目标值
 * - 同时维护当前待转换的边（有的边没了，有的边需要更换起点
 * - 这样就是暴力做法，得到最少的转换次数
 *
 * 当然还有题解的做法：
 * - 首先建图：每一个需要改变的字符对之间都加边（u - v）
 * - 因为反向边肯定直接特判无效了，所以可以直接加双边
 * - 对于每一个存在拓扑序且无环的弱连通分量 C ，所有边跑一次是 |C - 1| 次操作
 * - 所以可以对于构建的图中找这样的分量个数，找到一个答案就减去 1
 * - 对于不存在该图中的节点，也会自动的被考虑成一个分量，并减去自己的贡献
 * 所以就可以得到这个题目的答案
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <cstring>
#include <functional>

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

bitset<20> x;

void DFS(int u)
{
    x[u] = true;
    FWS::forEach(u, [&](auto e)
    { if (!x[e.v]) DFS(e.v); });
};

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
        bool ok = true;
        FWS::init(20);
        for (int i = 0; i < n; ++ i)
        {
            FWS::addBiEdge(a[i] - 'a', b[i] - 'a');
            if (a[i] > b[i]) {ok &= false; break;}
        }
        if (!ok) {cout << -1 << endl; continue;}
        x.reset();
        int ans = 20;
        for (int i = 0; i < 20; ++ i)
            if (!x[i]) DFS(i), -- ans;
        cout << ans << endl;
    }

    return 0;
}