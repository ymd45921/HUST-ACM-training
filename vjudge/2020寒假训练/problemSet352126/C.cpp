/**
 * @luogu P2885 (USACO07NOV)
 *
 * dp[i][j] = min(dp[i-1][k]+c*|j-k|) + (j-h[i])²
 * 单调队列优化的动态规划
 *
 * …………不过反正我还是没有看懂着动态规划是怎么看出来的
 * 
 * 看出来了。不知道是不是答案的影响
 * 但是我觉得这确实是动脑筋就能想出来的结果
 * 练习基本功的题目死好多次
 * 稍微动脑子的题目又不愿意去多想
 * 这算得上是训练吗？
 */
#include <iostream>
#include <cstdlib>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;
const int INF = (1<<31)-1;

int n,c,last;
int height[100010]{0};
int maxheight = 0;
int dp[100010][105]{0};

int solution()
{
    for(int i=height[1]+1;i<=maxheight;++i)
        dp[1][i] = (i-height[1])*(i-height[1]);
    for(int i=2;i<=n;++i)
    {
        last = height[i-1];
        for(int j=height[i];j<=maxheight;++j)
        {
            while(dp[i-1][last]+abs(j-last)*c>dp[i-1][last+1]+abs(j-last-1)*c
                  && last<maxheight)
                ++last;
            dp[i][j] = dp[i-1][last]+abs(j-last)*c+(j-height[i])*(j-height[i]);
        }
    }

    int ans = (1<<31)-1;
    for(int i=height[n];i<=maxheight;++i)
        ans = min(ans,dp[n][i]);
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>c;
    for(int i=1;i<=n;++i)
    {
        cin>>height[i];
        maxheight = max(maxheight,height[i]);
    }

    cout<<solution();
    return 0;
}