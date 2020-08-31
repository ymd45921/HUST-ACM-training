#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

#define same(u,v) (sccId[u]==sccId[v])
#define cleanDis() memset(dis,0,sizeof dis)
#define V e[c].to

using namespace std;
typedef vector<int> arrays;
struct edge {int to,next;};

const int N = 1e5 + 5;
const int M = 1e6 + 5;
int n,m;

namespace FrontStar
{
    int head[N];
    edge e[M];
    int tot = -1;
}

namespace Tarjan
{
    int dfn[N], low[N];
    int nextDfn = 1;
    bool instack[N];
    stack<int> s;
}

namespace SCCcomponent
{
    int cnt;
    int sccId[N];       // 顶点属于的SCC分量
    int id[N];          // 顶点在分量内的编号
    arrays group[N];    // SCC分量包含的点
    int dis[6][6];
    bool visit[N];
    arrays inEdge[N];   // 分量内的边
}

namespace DAGgraph
{
    int in[N];
    queue<int> q;
    int tmp[N], dp[N];
}

inline void init()
{
    using namespace Tarjan;
    using namespace FrontStar;
    using namespace SCCcomponent;
    using namespace DAGgraph;
    memset(head, -1, sizeof(int) * (n + 1));
    memset(dfn,0,sizeof(int)*(n+1));
    memset(low,0,sizeof(int)*(n+1));
    memset(sccId, 0, sizeof(int) * (n + 1));
    memset(id,0,sizeof(int)*(n+1));
    memset(tmp,0,sizeof(int)*(n+1));
    memset(dp,0,sizeof(int)*(n+1));
    memset(in, 0, sizeof(int) * (n + 1));
    memset(instack,0,sizeof(bool)*(n+1));
    memset(visit,0,sizeof(bool)*(n+1));
    tot = -1; cnt = 0; nextDfn = 1;
}

inline void addedge(int u, int v)
{
    using namespace FrontStar;
    e[++tot] = {v,head[u]};
    head[u] = tot;
}

void tarjan(int U)
{
    using namespace Tarjan;
    using namespace SCCcomponent;
    using namespace FrontStar;
    
    dfn[U] = low[U] = nextDfn++;
    s.push(U);
    instack[U] = true;

    int c = head[U];
    while (~c)
    {
        if (!dfn[V])
        {
            tarjan(V);
            low[U] = min(low[U], low[V]);
        }
        else if (instack[V])
            low[U] = min(low[U], low[V]);
        c = e[c].next;
    }

    if (dfn[U] == low[U])
    {
        int cur, tagId = 0;
        ++cnt;
        do
        {
            cur = s.top(); s.pop();
            instack[cur] = false;
            sccId[cur] = cnt;
            group[cnt].push_back(cur);
            id[cur] = ++tagId;
        } while (cur != U);
    }
}

void dfs(int now, int raw, int length)
{
    using namespace SCCcomponent;
    dis[id[raw]][id[now]] = max(dis[id[raw]][id[now]], length);
    visit[now] = true;
    for (auto that : inEdge[now])
        if (!visit[that]) dfs(that, raw, length + 1);
    visit[now] = false;
}

inline void topsort()
{
    using namespace DAGgraph;
    using namespace SCCcomponent;
    using namespace FrontStar;

    for (int i=1; i <= cnt; ++i)
        if (!in[i]) q.push(i);
    while (!q.empty())
    {
        int now = q.front(); q.pop();
        cleanDis();
        for (auto node : group[now])
            dfs(node,node,0);
        for (auto i : group[now])
            for (auto j : group[now])
                tmp[i] = max(tmp[i],dp[j]+dis[id[j]][id[i]]);
        for (auto node : group[now])
            dp[node] = tmp[node];
        for (auto U : group[now])
        {
            int c = head[U];
            while (~c)
            {
                if (!same(U, V))
                {
                    dp[V] = max(dp[V], dp[U] + 1);
                    --in[sccId[V]];
                    if (!in[sccId[V]])
                        q.push(sccId[V]);
                }
                c = e[c].next;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    init();
    int u,v;
    while (m--)
    {
        cin>>u>>v;
        addedge(u,v);
    }

    using namespace Tarjan;
    using namespace SCCcomponent;
    using namespace DAGgraph;
    using namespace FrontStar;

    for (int i=1;i<=n;++i)
        if (!dfn[i]) tarjan(i);
    cerr << "SCC component count: " << cnt << endl;
    for (int i=1;i<=n;++i)
    {
        int c = FrontStar::head[i];
        while (~c)
        {
            if (same(i, e[c].to))
                inEdge[i].push_back(e[c].to);
            else ++in[sccId[e[c].to]];
            c = e[c].next;
        }
    }
    topsort();

    int ans = 0;
    for (int i=1;i<=n;++i)
        ans = max(ans,dp[i]);
    cout<<ans+1<<endl;

    return 0;
}