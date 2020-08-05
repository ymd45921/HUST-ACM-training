/**
 * 
 */
#include <iostream>
#include <cstdio>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs modl = 1e9+7;

longs dmg[2060][2060]{0};
longs ans = 0;
int n,m,h,x,y,z;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m>>h;
    longs sumn = ((1+n)*n)>>1;
    longs summ = ((1+m)*m)>>1;
    longs nm = n*m;
    while(h--)
    {
        cin>>x>>y>>z;
        // dmg[x][y] -= z;
        // for(int i=1;i<=m;++i) dmg[x][i]=(dmg[x][i]+z)%modl;
        // for(int i=1;i<=n;++i) dmg[i][y]=(dmg[i][y]+z)%modl;
        // ans += (m+n-1)*z; ans%= modl;
        ans += (summ+sumn+m*x+n*y-x-y)%modl*z;
        ans %= modl;

    }
    // for(int i=1;i<=m;++i) 
    // {
    //     for(int j=1;j<=n;++j)
    //     // cout<<dmg[i][j]<<' ';
    //     ans = (ans+dmg[i][j]*(i+j))%modl;
    //     // cout<<endl;
    // }
    cout<<ans<<endl;

    return 0;
}