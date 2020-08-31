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
int inDegree[20010];

int dfn[20010];
int low[20010];
bool inStack[20010];
int nextDfn;
stack<int> desk;

int belong[20010];
int sccIn[20010];
int sccOut[20010];
int nextSCC;

int INcnt,OUTcnt;

inline void addedge(int u,int v)
{
    edgelist[u].push_back(v);
    ++inDegree[v];
}

inline void tarjan(int thispoint)
{
    dfn[thispoint] = low[thispoint] = nextDfn++;
    desk.push(thispoint);
    inStack[thispoint] = true;

    for(auto i : edgelist[thispoint])
    {
        if(!dfn[i])
        {
            tarjan(i);
            low[thispoint] = min(low[thispoint],low[i]);
        }
        else if(inStack[i])
            low[thispoint] = min(low[thispoint],low[i]);
    }

    if(dfn[thispoint]==low[thispoint])
    {
        int cur;
        ++nextSCC;
        do
        {
            cur = desk.top();
            desk.pop();
            inStack[cur] = false;
            belong[cur] = nextSCC;
        } while (thispoint-cur);
    }
}

inline void initialize()
{
    memset(belong,0,sizeof(belong));
    memset(sccIn,0,sizeof(sccIn));
    memset(sccOut,0,sizeof(sccIn));
    memset(inDegree,0,sizeof(inDegree));
    for(int i=1;i<=n;++i)   // 是[1,n]啊kora，你在初始化什么啊团长！
        edgelist[i].clear();
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(inStack,0,sizeof(inStack));
    nextDfn = 1;
    nextSCC = INcnt = OUTcnt = 0;
}

inline void newSCCgraph()
{
    for(int i=1;i<=n;++i)
        for(int edge : edgelist[i])
            if(belong[i]-belong[edge])
            {
                ++sccIn[belong[edge]];
                ++sccOut[belong[i]];
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
        if(nextSCC==1)
        {
            cout<<0<<endl;
            continue;
        }
        newSCCgraph();
        for(int i=1;i<=nextSCC;++i)
        {
            if(!sccIn[i])++INcnt;
            if(!sccOut[i])++OUTcnt;
        }
        cout<<max(INcnt,OUTcnt)<<endl;
    }
}