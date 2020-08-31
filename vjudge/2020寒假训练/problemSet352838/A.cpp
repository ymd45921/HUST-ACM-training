/**
 *
 * LCA，多维护一个距离
 * 
 * WA: 先改dis再递归，不然dis[itsfather]无意义
 */
#include <iostream>
#include <cstring>
#include <utility>

#define to second
#define len first

using namespace std;
typedef pair<int,int> edge;

int t,n,m;
int i,j,k;
int found;
int ans;

// front-star
edge elist[80005];
int ptr;
int nextptr[80005];
int head[40005]{0};

// lca
int depth[40005];
int dis[40005];
int father[40005][30];
int lg2[40005]{0};

inline void initialize()
{
    memset(head,0,sizeof(head));
    ptr = 0;
    memset(father,0,sizeof(father));
    memset(depth,0,sizeof(depth));
    dis[1] = dis[0] = 0;
}

inline void addedge(int u,int v,int distance)
{
    ++ptr;
    nextptr[ptr] = head[u];
    head[u] = ptr;
    elist[ptr] = {distance,v};
}

inline void dfs(int thispoint,int itsfather)
{
    depth[thispoint] = depth[itsfather]+1;
    father[thispoint][0] = itsfather;
    for(int it=1;it<=lg2[depth[thispoint]];++it)
        father[thispoint][it] = father[father[thispoint][it-1]][it-1];
    for(int it=head[thispoint];it;it=nextptr[it])
        if(elist[it].to!=itsfather)
        {
            dis[elist[it].to] = dis[thispoint]+elist[it].len;
            dfs(elist[it].to,thispoint);
        }
}

inline int lca(int a,int b)
{
    if(depth[a]<depth[b])swap(a,b);
    while(depth[a]>depth[b])
        a = father[a][lg2[depth[a]-depth[b]-1]];
    if(a==b) return a;
    for(int it=lg2[depth[a]];it>=0;--it)
        if(father[a][it]!=father[b][it])
        {
            a = father[a][it];
            b = father[b][it];
        }
    return father[a][0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // log2 常数优化
    for(int x=1;x<=40001;++x)
    lg2[x] = lg2[x-1]+(1<<lg2[x-1]==1);

    cin>>t;
    while(t--)
    {
        initialize();
        cin>>n>>m;
        for(int iter=1;iter<n;++iter)
        {
            cin>>i>>j>>k;
            addedge(i,j,k);
            addedge(j,i,k);
        }

        dfs(1,0);

        while(m--)
        {
            cin>>i>>j;
            found = lca(i,j);
            ans = dis[i]+dis[j]-(dis[found]<<1);
            cout<<ans<<endl;
        }
    }

    return 0;
}
