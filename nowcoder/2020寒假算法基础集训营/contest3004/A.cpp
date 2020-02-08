/**
 * 
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 1e9 + 7;
int n,m;
char map[60][60];
longs dp[60][60];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        for(int i=1;i<=n;++i)
            cin>>(map[i]+1);
        memset(dp,0,sizeof(dp));
        dp[1][1] = 1;
        for(int i=1;i<=n;++i)
            for(int j=1;j<=m;++j)
            {
                dp[i][j]%=MOD;
                switch(map[i][j])
                {
                case 'R':
                    dp[i][j+1] += dp[i][j];
                    break;
                case 'D':
                    dp[i+1][j] += dp[i][j];
                    break;
                case 'B':
                    dp[i][j+1] += dp[i][j];
                    dp[i+1][j] += dp[i][j];
                    break;
                default: break;
                }
            }
        cout<<dp[n][m]%MOD<<endl;
    }

    return 0;
}