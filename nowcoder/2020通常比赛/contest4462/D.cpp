/**
 * 
 * 因为任意两点的最短路必然在最小生成树上
 * 所以最小生成树是必然要找的——不对。感觉不对劲。
 * 
 * 我操枚举你的阿妈呢？
 * 确实，10*10，不搜白不搜（
 * 
 * 还有值得一提的是相关的状压和TSP问题
 * 状压DP也可以做这个题目
 */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <cstring>

#define rint register int

using namespace std;
typedef long long longs;
typedef long double longd;

const char mod[] = "The shortest path has length ";

struct coord
{
    int x,y;
    int operator-(const coord& c);
};

int t,N,M,n;
coord st,pp[20];
int dis[20][20];
int dp[1<<11][20];  // dp数组：经过点的状压标记，最后到达的点

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>t) while(t--)
    {
        cin>>N>>M>>st.x>>st.y;
        cin>>n;
        pp[0] = st;
        for(int i=1;i<=n;++i)
            cin>>pp[i].x>>pp[i].y;
        for(int i=0;i<=n;++i)
            for(int j=i;j<=n;++j)
                dis[i][j]=dis[j][i]=pp[i]-pp[j];
        memset(dp,0x3f,sizeof(dp));
        const int lim = (1<<n+1)-1;
        dp[0][0] = dp[1][0] = 0;    // 1（1<<0) 是起点
        for(rint i=1;i<=lim;++i)    // i是状压标记：记录经过的点
            for(int j=0;j<=n;++j)
                if(i>>j&1)          // 找到了一个已经经过了的点j
                    for(int k=0;k<=n;++k)
                        if(i>>k&1)  // 再找到一个经过了的点k
                            dp[i][j]=min(dp[i][j],dp[i^(1<<j)][k]+dis[k][j]);
        int ans = 0x7fffffff;
        for(int i=1;i<=n;++i)       // 从每种经过所有点的情况回到起点
            ans = min(ans,dp[lim][i]+dis[i][0]);
        cout<<mod<<ans<<endl;

    }

    return 0;
}

int coord::operator-(const coord& c)
{
    return abs(x-c.x)+abs(y-c.y);
}