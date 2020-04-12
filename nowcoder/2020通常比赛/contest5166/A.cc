/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <functional>
#include <queue>

#define Continue return true
#define Break return false
#define Return return true

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 30, M = 2e5 + 5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

bool op[N], ed[N];
int xx[N];

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

    const int n = 26;

    void init()
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        op[u] |= true; ed[v] |= true;
//        if (u == v)
//        {
//            xx[u] += w;
//            return;
//        }
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
    }

    inline void foreach(int st, const function<bool(int,edge&)>& func)
    {
        for (int c = head[st]; ~c; c = ee[c].next)
            if (!func(c, ee[c])) break;
    }
}

namespace DFS
{
    bool vis[M];
    int __lim, __st;
    int dfn[M];

    void init(int m)
    {
        memset(vis, 0, sizeof(bool)*(m+1));
        memset(dfn, 0, sizeof(bool)*(m+1));
    }

    int dfs(int u, int len)
    {
        int ans = -1;
        for (int c = FWS::head[u]; ~c; c = FWS::ee[c].next)
        {
            edge& e = FWS::ee[c];
            if (vis[c]) continue;
            int v = e.v;
            int dis = len + e.w;
            if (v == __st)
            {
                ans = max(ans, dis);
                continue;
            }
            vis[c] = true;
            int nex = dfs(v, dis);
            vis[c] = false;
            ans = max(ans, nex);
        }
        return ans;
    }

    int brute()
    {
        int ans = 0;
        for (int i = 0; i < 26; ++ i)
            if (op[i] && ed[i])
            {
                __st = i;
                ans = max(ans, dfs(i,0));
            }
        return ans;
    }

    int find(int len, int u)
    {
        int ans = -1;
        FWS::foreach(u, [&](int c, edge& e) -> bool
        {
            if (vis[c]) Continue;
            int v = e.v;
            int path = len + e.w;
            if (v == __st)
            {
                ans = max(ans, path);
                Continue;
            }
            vis[c] = true;
            int maxx = find(path, v);
            vis[c] = false;
            Return;
        });
        return ans;
    }

    bool f(int mid)
    {
        __lim = mid;
        for (int i = 0; i < 26; ++ i)
        {
            __st = i;
            if (find(0,i) >= mid)
                return true;
        }
        return false;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    FWS::init();
    memset(xx, 0, sizeof xx);

    int n; string s; longs sum = 0;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> s;
        int len = s.length();
        FWS::addedge(s[0]-'a', s[len-1]-'a', len);
        sum += len;
    }

    DFS::init(n);
    cout << DFS::brute() << endl;
//    int l = 0, r = sum;
//    while (l < r)
//    {
//        int m = (l + r) >> 1;
//        if (DFS::f(m)) l = m+1;
//        else r = m-1;
//    }
//    cout << l;

    return 0;
}