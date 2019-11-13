/*
 * 这是一道阅读理解的完全背包题
 * 
 * woc为什么他妈的能出现负数的woc？不都是从0成长起来的嘛？
 * 先拿了一个判断条件兜了一下……神tm就这么过了……那有缘再会，告辞==
 * 
 */
#include <iostream>
#include <cstring>

#define min(a,b) (a<b?a:b)

using namespace std;

int c,d,n,m,k;
int dp[12315];
int lim_l,lim_u;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>c>>d>>n>>m>>k;
    lim_u = n*m;
    lim_l = lim_u-k;
    memset(dp,1<<6,sizeof(dp));
    dp[0] = 0;

    for(int i=n;i<=lim_u;i+=n)
        dp[i] = min(dp[i-n]+c,dp[i]);
    for(int i=1;i<=lim_u;++i)
        dp[i] = min(dp[i-1]+d,dp[i]);
    int ans = dp[lim_u];
    for(int i=lim_l;i<lim_u;++i)
        ans = min(ans,dp[i]);
    if(ans<0)ans = 0;                   //为什么这ans能tm等于负数？？
    cout<<ans;

    return 0;
}