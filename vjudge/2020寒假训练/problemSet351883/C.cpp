/**
 * 我日这个题目可以使用二分来确认答案
 * 然后可以在一定时间内判断答案是否正确
 * 既然判断好写那为啥不二分？
 *
 * 答案————最好情况：等差数列，且差值尽量小
 * 
 * 二分check函数：
 * dp[i]：指的是从第i~第n个数列成员最少需要的修改次数，最多不超过成员数n-i-1
 * 在区间[1,n]的子集[i,j]上进行查找，从最简单的情况(i,i+1)开始测试
 * 如果a[j]-a[i]的差距符合这个candidate的要求，就可以更新dp[i]的值
 * 如果调整[i,j]和调整[j,n]的和比现在调整[i,n]要少，就更新dp[i]的值
 * 如果dp[i]+i（dp[i]是[i,n]的最好情况，i是[0,i]的最坏情况）比要求k小，则满足
 * 二分：如果差距candidate满足了，比candidate大的差距必然满足。
 * 应当缩小右侧边界寻找可能的更小的candidate作为最优解。
 */
#include <iostream>
#include <cmath>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;
typedef long long longs;

int n,k;
int a[2060];
int dp[2060];

inline int c(const int a[], int n)
{
    if(n<=1&&n>=0)return 0;
    int ans = 0;
    for(int i=1,j=2;j<=n;++i,++j)
        ans = max(ans,abs(a[j]-a[i]));
    return ans;
}

inline bool check(longs candidate)
{
    for(int i=n;i>0;--i)
    {
        dp[i] = n-i-1;
        for(int j=i+1;j<=n;++j)
            if(abs(a[j]-a[i])<=candidate*longs(j-i))
                dp[i] = min(dp[i],dp[j]+j-i-1);
        if(dp[i]+i<=k)return true;
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];

    longs l = 0,r = 2E9+1,mid;
    while(l<r)
    {
        mid = (l+r)>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }

    cout<<r;
    return 0;
}