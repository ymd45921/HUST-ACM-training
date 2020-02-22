/**
 * 
 * 怎么害段错误的== 交错题了==
 * 
 * int杀我妈
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs inf = 0x7fffffffffffffff;

int a[100005];
// int vis[100005];
vector<int> el[100005];
longs ans = -inf;

longs dfs(int node, int p)
{
    longs f=0,s=0;
    for(int c : el[node])
    {
        if(c==p)continue;
        else
        {
            longs r = dfs(c,node);
            if(r>f){s=f;f=r;}
            else if(r>s){s=r;}
        }
    }
    longs tmp = f+a[node];
    longs li = tmp+s;
    if(li>ans) ans = li;
    return tmp;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,u,v;

    cin>>n;
    // memset(vis,-1,sizeof(int)*(n+1));
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<n;++i)
    {
        cin>>u>>v;
        el[u].push_back(v);
        el[v].push_back(u);
    }
    dfs(1,0);
    cout<<ans<<endl;

    return 0;
}