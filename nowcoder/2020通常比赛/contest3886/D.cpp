/**
 * 
 * 我操，经典背包问题
 * 我操，只买一种包装
 * 真jb水题
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long longs;

struct pencil
{
    int price,number;
};

pencil c[3];
int dp[40010]{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while(cin>>n)
    {
        for(int i=0;i<3;++i)
            cin>>c[i].number>>c[i].price;
        memset(dp,0x3f,sizeof dp);
        dp[0] = 0;
        for(int i=0;i<3;++i)
        {
            int tmp = 0;
            pencil &p = c[i];
            for(int j=p.number,k=0;j<=40000;++j,++k)
                dp[j] = min(dp[j],dp[k]+p.price);
        }
        sort(dp+n,dp+40001);
        cout<<dp[n]<<endl;
    }

    return 0;
}