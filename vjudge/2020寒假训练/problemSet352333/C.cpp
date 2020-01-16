/**
 * 
 * 遇事不决考虑DP？
 */
#include <iostream>
#include <cstring>

using namespace std;

int t,m,n;
int ans,in;
bool input[11];

int dp[13][13]{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    for(int i=1;i<=t;++i)
    {
        cin>>m>>n;
        memset(input,0,sizeof(input));
        memset(dp,0,sizeof(dp));
        ans = 0;
        for(int j=0;j<m;++j)
        {
            cin>>in;
            input[in] = true;
            dp[1][in] = 1;  
        }
        for(int j=2;j<=n;++j)
        for(int k=1;k<=9;++k)
        {
            if(!input[k])continue;
            dp[j][k] = dp[j-1][k]+dp[j-1][k+1]+dp[j-1][k+2];
            if(k==1)continue;
            dp[j][k] += dp[j-1][k-1]+dp[j-1][k-2];
        }
        for(int j=1;j<=9;++j)
            ans+=dp[n][j];
        cout<<"Case "<<i<<": "<<ans<<endl;
    }
}