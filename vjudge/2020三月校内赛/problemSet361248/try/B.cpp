/**
 *
 * SCC缩点（Tarjan） + DAG-dp（TopSort）
 *
 * 给了10s+512M内存
 *
 * 整体过程：
 * 建图 -> 缩点，留存SCC信息 -> 构建SCC新图（分量内+入度统计）
 *  -> 拓扑排序 -> DFS扫描组件内最长距离 -> 拓扑更新DP统计答案
 *
 * Debug 后记：
 * 全局变量一时爽，错误调试火葬场
 * 这 u v ，我看下次谁敢开全局
 *
 * - 前向星没有初始化为-1
 * - 三张图混淆，遍历时用错了图
 * - 没有使用循环内的局部变量，使用了全局uv
 * - dfs 传值错误
 */
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

#define thatpoint e[c].to
#define nextedge e[c].next
#define same(u,v) (belong[u]==belong[v])
#define cleanDis() memset(dis,0,sizeof dis)

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;
typedef vector<int> arrays;
struct edge {int to,next;};

const int N = 1e5 + 5;
const int M = 1e6 + 5;
int n,m;

int head[N];        // 前向星
edge e[M];
int tot = -1;

int dfn[N], low[N]; // Tarjan基本
int nextDfn = 1;
bool instack[N];
stack<int> s;

int sccId;          // SCC点的信息
int belong[N];
int id[N];
arrays group[N];

int dis[6][6];      // 缩点内DFS
bool visit[N];
arrays inEdge[N];

int indegree[N];    // TopSort-DAGdp
queue<int> q;
int tmp[N], dp[N];

inline void init()
{
    memset(head,-1,sizeof(int)*(n+1));
    memset(dfn,0,sizeof(int)*(n+1));
    memset(low,0,sizeof(int)*(n+1));
    memset(belong,0,sizeof(int)*(n+1));
    memset(id,0,sizeof(int)*(n+1));
    memset(tmp,0,sizeof(int)*(n+1));
    memset(dp,0,sizeof(int)*(n+1));
    memset(indegree,0,sizeof(int)*(n+1));
    memset(instack,0,sizeof(bool)*(n+1));
    memset(visit,0,sizeof(bool)*(n+1));
    tot = -1; sccId = 0; nextDfn = 1;
}

inline void addedge(int u, int v)
{
    e[++tot] = {v,head[u]};
    head[u] = tot;
}

void tarjan(int thispoint)
{
    dfn[thispoint] = low[thispoint] = nextDfn++;
    s.push(thispoint);
    instack[thispoint] = true;

    int c = head[thispoint];
    while (~c)
    {
        if (!dfn[thatpoint])
        {
            tarjan(thatpoint);
            low[thispoint] = min(low[thispoint],low[thatpoint]);
        }
        else if (instack[thatpoint])
            low[thispoint] = min(low[thispoint],low[thatpoint]);
        c = nextedge;
    }

    if (dfn[thispoint] == low[thispoint])
    {
        int cur, tmpId = 0;
        ++sccId;
        do
        {
            cur = s.top(); s.pop();
            instack[cur] = false;
            belong[cur] = sccId;
            group[sccId].push_back(cur);
            id[cur] = ++tmpId;
        } while (cur != thispoint);
    }
}

void dfs(int x, int y, int dist)
{
    dis[id[y]][id[x]] = max(dis[id[y]][id[x]],dist);
    visit[x] = true;
    for (auto that : inEdge[x])
        if (!visit[that]) dfs(that,y,dist+1);
    visit[x] = false;
}

inline void topsort()
{
    for (int i=1;i<=sccId;++i)
        if (!indegree[i]) q.push(i);
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
        for (auto thispoint : group[now])
        {
            int c = head[thispoint];
            while (~c)
            {
                if (!same(thispoint,thatpoint))
                {
                    dp[thatpoint] = max(dp[thatpoint],dp[thispoint]+1);
                    --indegree[belong[thatpoint]];
                    if (!indegree[belong[thatpoint]])
                        q.push(belong[thatpoint]);
                }
                c = nextedge;
            }
        }
//        for (auto u : group[now])
//            for (auto v : inEdge[u])
//                if (!same(u,v))
//                {
//                    dp[v] = max(dp[v],dp[u]+1);
//                    --indegree[belong[v]];
//                    if (!indegree[belong[v]]) q.push(v);
//                }
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

    for (int i=1;i<=n;++i)
        if (!dfn[i]) tarjan(i);
    cerr<<"SCC component count: "<<sccId<<endl;
    for (int i=1;i<=n;++i)
    {
        int c = head[i];
        while (~c)
        {
            if (same(i,thatpoint))
                inEdge[i].push_back(thatpoint);
            else ++indegree[belong[thatpoint]];
            c = nextedge;
        }
    }
    topsort();

    int ans = 0;
    for (int i=1;i<=n;++i)
        ans = max(ans,dp[i]);
    cout<<ans+1<<endl;

    return 0;
}