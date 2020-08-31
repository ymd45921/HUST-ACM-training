/**
 *
 * 那么，原版的最大环应该怎么解呢？
 *
 * 纯DP还是有不少坑的==
 * 一堆傻逼错误（）
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <functional>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 30, M = 2e5 + 5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;


int dp[N][N];

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
    bool op[N], ed[N];

    const int n = 26;

    void init()
    {
        memset(head, -1, sizeof(int)*(n+1));
        memset(op, 0, sizeof op);
        memset(ed, 0, sizeof ed);
        tot = 0;
    }

    void addedge(int u, int v, int w)
    {
        op[u] |= true; ed[v] |= true;
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
        using FWS::op; using FWS::ed;
        for (int i = 0; i < 26; ++ i)
            if (op[i] && ed[i])
            {
                __st = i;
                ans = max(ans, dfs(i,0));
            }
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    FWS::init();

    auto ff = [&]() -> void             // 炸了
    {
        memset(dp, 0, sizeof dp);
        using FWS::ee; using FWS::tot;
        for (int i = 0; i < tot; ++ i)
        {
            edge& ii = ee[i];
            for (int j = 0; j < 26; ++ j)
                dp[j][ii.v] = max(dp[j][ii.v], dp[j][ii.u]+ii.w);
        }
    };

    auto log = [&]()
    {
        for (int i = 0; i < 26; ++ i)
        {
            for (int j = 0; j < 26; ++ j)
                cerr << dp[i][j] << ' ';
            cerr << endl;
        }
    };

    auto f = [&]() -> void
    {
        memset(dp, 0, sizeof dp);
        using FWS::ee; using FWS::tot;
        for (int i = 0; i < tot; ++ i)
        {
            edge& ii = ee[i];
            for (int j = 0; j < 26; ++ j)
                if(dp[j][ii.u] || j == ii.u)
                    dp[j][ii.v] = max(dp[j][ii.v], dp[j][ii.u]+ii.w);
        }
    };

    int n; string s; longs sum = 0;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> s;
        int len = s.length();
        FWS::addedge(s[0]-'a', s[len-1]-'a', len);
        sum += len;
    }

    // DFS::init(n);
    // cout << DFS::brute() << endl;
    f(); int ans = 0;
    log();

    for (int i = 0; i < 26; ++ i)
//        if (FWS::op[i] && FWS::ed[i])
            ans = max(ans, dp[i][i]);
    cout << ans << endl;

    return 0;
}