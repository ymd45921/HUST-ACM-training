/**
 *
 * 第一感觉：树上LCA 并查集
 *
 * 屁啦，是最小生成树==
 * 
 * 遭鬼原因：初始化不彻底，数组从0/1开始混乱。
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;
struct edge
{
    int from,to,val;
    bool operator<(const edge& rhs) const;
};

const string yes = "Yes";
const string no = "No";
const int N = 505;

int n;
int map[N][N];
edge elist[N*N];
int cur = 0;        // 输入的完全图边光标
bool fall = false;
int dis[N][N];      
int ufs[N];         // Kruskal用并查集

int head[N];        // 前向星存最小生成树
edge fstree[N*2];
int nextptr[N*2];
int tot;

int father(int x)
{
    if(!ufs[x]) return x;
    else return ufs[x]=father(ufs[x]);
}

inline int unite(int u,int v)
{
    return ufs[u] = v;
}

inline void addedge(edge& e)
{
    nextptr[tot] = head[e.from];
    head[e.from] = tot;
    fstree[tot] = e;
    ++tot;
    nextptr[tot] = head[e.to];
    head[e.to] = tot;
    fstree[tot] = {e.to,e.from,e.val};
    ++tot;
}

void dfs(int now,int prev,int sp,int leng)
{
    dis[sp][now] = leng;
    int c = head[now];
    while(~c)
    {
        edge& ce = fstree[c];
        if(ce.to^prev)
            dfs(ce.to,now,sp,leng+ce.val);
        c = nextptr[c];
    }
}

inline void init()
{
    fall = false;
    memset(ufs,0,sizeof(int)*(n+1));
    tot = 0;
    memset(head,-1,sizeof(int)*(n+1));
    cur = 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        init();
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                cin>>map[i][j];

        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
                if(map[i][j]!=map[j][i])    // 简单筛查
                {
                    cout<<no<<endl;
                    fall = true;
                    break;
                }
                else elist[cur++] = {i,j,map[i][j]};
            if(fall) break;
        }
        if(fall) continue;

        sort(elist,elist+cur);
        const int ne = n-1<<1;

        for(int i=0;i<cur&&tot<ne;++i)      // Kruskal找树
        {
            int fu=father(elist[i].from),fv=father(elist[i].to);
            if(fu!=fv)
            {
                unite(fu,fv);
                addedge(elist[i]);
            }
        }
        for(int i=1;i<=n;++i) dfs(i,0,i,0); // 找i到所有点的距离

        for(int i=1;i<=n;++i)
        {
            for(int j=i+1;j<=n;++j)
                if(map[i][j]!=dis[i][j])    // 二度核对
                {
                    cout<<no<<endl;
                    fall = true;
                    break;
                }
            if(fall) break;
        }
        if(fall) continue;

        cout<<yes<<endl;
        for(int i=0;i<tot;i+=2)
            cout<<fstree[i].val<<endl;
    }

    return 0;
}

bool edge::operator<(const edge& rhs) const
{
    return val<rhs.val;
}