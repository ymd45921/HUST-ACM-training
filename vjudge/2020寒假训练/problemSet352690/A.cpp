/**
 * 
 * 因为每个SCC都是最大强连通块，所以必然最多只有一种边（出/入）
 * 让它和其他强连通块强连通：既有出又有入即可
 * 为了确保这一点，缺入边和缺出边的应该选择较大者————
 * 特判没有边和完全边的情况————虽然感觉也不太必要。
 * 
 * SF: 不知怎得，输出答案总是大一. 微妙的问题。没事了
 * WA: 日，怎么还能wa了……你特判都不跳转的🐎团长？你在做什么啊
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;

int n,m;
int u,v;
vector<int> edgelist[20010];
int indegree[20010];

//tarjan
int dfn[20010];
int low[20010];
bool instack[20010];
int nextdfn;
stack<int> desk;

// scc new graph
// vector<int> scclist[20010];
int belong[20010];
int sccin[20010];
int sccout[20010];
int nextscc;

int incnt,outcnt;

inline void addedge(int u,int v)
{
    edgelist[u].push_back(v);
    ++indegree[v];
}

inline void tarjan(int thispoint)
{
    dfn[thispoint] = low[thispoint] = nextdfn++;
    desk.push(thispoint);
    instack[thispoint] = true;

    for(auto i : edgelist[thispoint])
    {
        if(!dfn[i])
        {
            tarjan(i);
            low[thispoint] = min(low[thispoint],low[i]);
        }
        else if(instack[i])
            low[thispoint] = min(low[thispoint],low[i]);
    }

    if(dfn[thispoint]==low[thispoint])
    {
        int cur;
        ++nextscc;
        do
        {
            cur = desk.top();
            desk.pop();
            instack[cur] = false;
            belong[cur] = nextscc;
        } while (thispoint-cur);
    }
}

inline void initialize()
{
    memset(belong,0,sizeof(belong));
    memset(sccin,0,sizeof(sccin));
    memset(sccout,0,sizeof(sccin));
    memset(indegree,0,sizeof(indegree));
    for(int i=1;i<=n;++i)   // 是[1,n]啊kora，你在初始化什么啊团长！
        edgelist[i].clear();
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(instack,0,sizeof(instack));
    nextdfn = 1;
    nextscc = incnt = outcnt = 0;
}

inline void countnewgraph()
{
    for(int i=1;i<=n;++i)
        for(int edge : edgelist[i])
            if(belong[i]-belong[edge])
            {
                ++sccin[belong[edge]];
                ++sccout[belong[i]];
            }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        initialize();
        if(!m)
        {
            if(n>1)cout<<n<<endl;
            else cout<<0<<endl;
            continue;
        }
        while(m--)
        {
            cin>>u>>v;
            addedge(u,v);
        }

        for(int i=1;i<=n;++i)
            if(!dfn[i])tarjan(i);
        if(nextscc==1)
        {
            cout<<0<<endl;
            continue;
        }
        countnewgraph();
        for(int i=1;i<=nextscc;++i)
        {
            if(!sccin[i])++incnt;
            if(!sccout[i])++outcnt;
        }
        cout<<max(incnt,outcnt)<<endl;
    }
}