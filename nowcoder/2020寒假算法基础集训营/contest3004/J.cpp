/**
 * 
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;
struct edge{int to,next;};
struct poke{longs t,p,val;};

int n,m,k,p,u,v;
int head[250];
edge edges[10086];
int tot;
poke pokemon[100010];
longs ans,t,val;

inline void init()
{
    memset(head,-1,sizeof(head));
    tot = 0;
    ans = 0ll;
}

void addedge(int u,int v)
{
    edges[tot] = {v,head[u]};
    head[u] = tot++;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        for(int i=0;i<m;++i)
        {
            cin>>u,v;
            addedge(u,v);
        }
        cin>>k;
        for(int i=0;i<k;++i)
        {
            cin>>t>>p>>val;
            pokemon[i] = {t,p,val};
        }
    }

    return 0;
}