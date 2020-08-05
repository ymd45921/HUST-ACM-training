#include <iostream>
#include <cstring>
#include <algorithm>

#define max(x,y) x>y?x:y
#define min(x,y) x<y?x:y

using namespace std;

int T;
double P,p[105];
int N,m[105],ans[105];
double dp[10005];
int sum = 0;

int main()
{
    cin>>T;
    for(int it=0;it<T;++it)
    {
        cin>>P>>N;
        sum = 0;
        for(int i=0;i<N;++i) {cin>>m[i]>>p[i];sum+=m[i];}
        memset(dp,1<<6,sizeof(dp));
        for(int i=0;i<N;++i)
        {
            for(int j=sum;j>=m[i];--j)
            {
                dp[j] = min(dp[j],dp[j-m[i]]+p[i]);
            }
        }
        sort(dp,dp+sum+1);//is neccessary?
        int cur = 0;
        for(;cur<=sum;++cur)
        {
            if(dp[cur]>=P)break;
        }
        ans[it] = dp[cur-1];
    }
    for(int i=0;i<T;++i)cout<<ans[i]<<endl;
}

