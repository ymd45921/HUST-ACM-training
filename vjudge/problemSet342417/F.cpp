#include <iostream>
#include <cstring>

#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)

using namespace std;

int a[20],b[20],c[20],d[20];
int n,m;
int dp[5][1050];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m>>c[0]>>d[0];
    a[0]=b[0]=0;
    for(int i=1;i<=m;++i)
    cin>>a[i]>>b[i]>>c[i]>>d[i];
    memset(dp,0,sizeof(dp));
    
    int col=0,row=0;
    for(int i=0;i<=m;++i)
    for(int j=0;j<=n;++j)
    {
        col = i&1;              //换成了这一句eg1=260就变回241了？
        if(b[i])row = min(j/c[i],a[i]/b[i]);
        else row = j/c[i];
        for(int k=0;k<=row;++k)
        dp[col][j] = max(dp[col][j],dp[!col][j-k*c[i]]+k*d[i]);
    }
    cout<<dp[m%2][n];

    return 0;
}