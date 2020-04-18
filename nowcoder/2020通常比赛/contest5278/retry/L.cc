/**
 *
 * 因为节点数是 S + T + 7Days + nTasks，
 * 所以FWS初始化需要传入的 'n' = n + 9
 *
 * 网络流的题目debug是真的烦人==
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
using longs = long long;

const int inf = 0x3f3f3f3f;
const int N = 1050, M = N * 8;
int n, e, c[N][8]{0}, sum = 0;
#define FN FlowNetwork

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

template <int _n, int _m = _n*_n>
class fws
{
    int head[_n+1];
    int tot;
    edge ee[_m];

public:
    class pointer : public iterator<forward_iterator_tag, edge>
    {
        int cur = -1;
        edge* ptr = nullptr;

        pointer () = default;

    public:
        pointer (int _x, edge* _y = nullptr) { cur = _x; ptr = _y; }

        pointer &operator =(const pointer &rhs)
        {
            cur = rhs.cur;
            ptr = rhs.ptr;
            return *this;
        }

        bool operator==(const pointer &rhs) const { return cur == rhs.cur && ptr == rhs.ptr; }

        bool operator!=(const pointer &rhs) const { return !(rhs == *this); }

        pointer &operator ++()
        {
            int d = ptr->next - cur;
            cur = ptr->next;
            ptr = ~cur ? ptr + d : nullptr;
            return *this;
        }

        pointer &operator ++(int)
        {
            auto tmp = *this;
            int d = ptr->next - cur;
            cur = ptr->next;
            ptr = ~cur ? ptr + d : nullptr;
            return tmp;
        }

        edge &operator *() { return *ptr; }
    };

    fws() {this->clear();}
    fws(int n) {this->clear(n);}

    void clear(int n = _n)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void add_edge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }

    typedef pointer iterator;

    edge &operator [](int ii) { return ee[ii]; }

    iterator begin(int u) { return pointer(head[u], &ee[head[u]]); }

    iterator end(int u = 0) { return pointer(-1, nullptr); }
};

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N-1)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }
}

namespace FlowNetwork
{
    using namespace FWS;

    int dis[N], __full, __cnt;
    int __S, __T;
    int __D[8], __P[N];

    auto __addedge = [](int u, int v, int w)
    {
        addedge(u, v, w);
        addedge(v, u, 0);
    };

    void makeGraph(int para)
    {
        FWS::init(n+9); __cnt = 0;              // 网络流节点数较多
        __S = ++ __cnt; __T = ++ __cnt;
        auto sdew = [&](int day)
        {
            int __x = para / 7 + (para % 7 >= day ? 1 : 0);
            return __x * e;
        };

        for (int i = 1; i <= 7; ++ i)
        {
            __D[i] = ++ __cnt;
            __addedge(__S, __D[i], sdew(i));
        }
        for (int i = 1; i <= n; ++ i)
        {
            __P[i] = ++ __cnt;
            __addedge(__P[i], __T, c[i][0]);
            for (int j = 1; j <= 7; ++ j)
                if (c[i][j]) __addedge(__D[i], __cnt, inf);
        }
    }

    bool bfs()
    {
        static queue<int> q;
        memset(dis, 0x3f, sizeof(int)*(__cnt+1));
        q.push(__S); dis[__S] = 0;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (int cc = head[u]; ~cc; cc = ee[cc].next)
            {
                edge& e = ee[cc]; int v = e.v, w = e.w;
                if (!w || dis[v] <= dis[u] + 1) continue;
                dis[v] = dis[u] + 1; q.push(v);
            }
        }
        return dis[__T] < inf;
    }

    int dfs(int u, int inflow)
    {
        if (u == __T) return inflow;
        int outflow = 0;
        for (int cc = head[u]; ~cc; cc = ee[cc].next)
        {
            edge &e = ee[cc]; int v = e.v, w = e.w;
            edge &r = ee[cc ^ 1];
            if (!w || dis[v] != dis[u] + 1) continue;
            int t = dfs(v, min(w, inflow - outflow));
            outflow += t; e.w -= t; r.w += t;
            if (inflow == outflow) break;
        }
        if (!outflow) dis[u] = 0;
        return outflow;
    }

    int dinic()
    {
        int ans = 0;
        while (bfs()) ans += dfs(__S, inf);
        return ans;
    }

    bool check(int mid)
    {
        if (e * mid < __full) return false;     // 本题优化
        makeGraph(mid);
        return dinic() == __full;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, x;
    memset(c, 0, sizeof c);
    cin >> n >> e;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> c[i][0] >> m;
        sum += c[i][0];
        while (m --)
        {
            cin >> x;
            ++ c[i][x];
        }
    }
    FN::__full = sum;

    int ll = 0, rr = inf / e, ans = -1;         // 防止 mid*e > int
    while (ll <= rr)
    {
        int mm = (ll + rr) / 2;
        if (FN::check(mm)) ans = mm --, rr = mm;
        else ll = ++ mm;
    }
    cout << ans << endl;

    return 0;
}