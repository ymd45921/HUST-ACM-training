/**
 *
 * 反向构建树，你敢说你没有想到？
 * 不是说队友的想法误导，还是自己不够坚定
 * 而且，要是想到答案这样合理的统计方法，你会不做这个题？
 *
 * 最熟练的队伍七分钟 A 这个题目，这才是简单题应该有的手速才是（
 *
 * 虽然我也不知道我们考场上的写法到底是哪里有问题，
 * 但是感觉那样削的话，简单的做法不满足要求，复杂的做法和暴力无异
 *
 * 怎么反向思考？
 * - 按照顺序：我们是大连通块删掉最小点变成小连通块，然后小连通块变更小
 * - 那么反过来：我们将小连通块使用更小的值连接成大连通块
 * - 按照顺序：拆连通块时答案增加最小值，通过拆点计算贡献
 * - 那么反过来：每两个较大连通块自己的贡献要减去这个最小值（共同贡献）
 * 所以代码要构建出关联小点是其关联的连通块的父节点的情况；
 *
 * 需要特别注意的就是构建树和并查集合并不是一个东西：
 * - 并查集这个东西的 join 是无所谓方向的，只要同一个祖先就可以
 * - 构建有根树时：需要严格保证将某个节点连接到它对应的祖先才可以
 * 这个题目如果不注意这个的话也会暴毙（
 * 但是因为这个题目中要使用并查集的父亲，所以 join 的方向是讲究的==
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
int b[N], xx[N], anc[N];
bitset<N> open;

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

    using method = void(*)(const edge &e);

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

    void foreach(int u, const method iter)
    {
        for (auto ii = head[u];
             ii != -1;
             ii = ee[ii].next)
            iter(ee[ii]);
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
        UFS::init(n + 1);
        FWS::init(n + 1);
        memset(anc, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; ++ i)
            cin >> b[i], xx[i] = i;
        sort(xx + 1, xx + 1 + n,
             [](int i, int j){return b[i] < b[j];});
        open.reset();
        while (m --)
        {
            int u, v;
            cin >> u >> v;
            FWS::addEdge(u, v);
            FWS::addEdge(v, u);
        }
        for (int i = n; i; -- i)
        {
            auto u = xx[i];
            open[u] = true;
            FWS::foreach(u, [](const edge &e)
            {
                auto v = e.v, u = e.u;
                using namespace UFS;
                if (!open[v] ||
                    father(u) == father(v)) return;
                anc[father(v)] = u;     // v 的祖先是确切的 u，但是根据操作顺序，此时 u 未被合并
                join(v, u);             // 将 v 合并到 u 上，并查集根始终是较小的点
            });
        }
        longs ans = 0;
        for (int i = 1; i <= n; ++ i)
            ans += b[i] - b[anc[i]];
        cout << ans << endl;
    }

    return 0;
}