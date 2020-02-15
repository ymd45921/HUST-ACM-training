/**
 * 
 * T了
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,in[1000010];
int v[1000010];
bool vis[1000010];
vector<int> noin;
int ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i) {cin>>v[i];++in[v[i]];}
        memset(in,0,sizeof(int)*(n+1));
        for(int i=1;i<=n;++i) if(!in[i])
        {
            memset(vis,0,sizeof(bool)*(n+1));
            int cnt = 1,cur = i; vis[i] = 1;
            while(!vis[v[cur]])
            {
                vis[v[cur]] = 1;
                cur = v[cur];
                ++cnt;
            }
            if(cnt>ans) ans = cnt;
        }
        cout<<ans<<endl;
        ans = 0;
    }

    return 0;
}