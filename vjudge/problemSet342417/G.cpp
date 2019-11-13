/* 
 * 有一股整数划分的香气==那好像就可以依据这个用DP做了
 * 但是和之前做过的整数划分有区别：有新的条件——包含大于d的项目
 * 将大于d的项目存在的可能性分别记录：这是可以实现的
 * 
 * - dp[i][0,1]:当选择的路径长度和为i，0表示不选择≥d的路，1表示选
 * - 很显然，令dp[0][0]=1;设j是当前考虑状态的最大长度，遍历j
 * - 当j<d时，有dp[i+j][0]+=dp[i][0];——等于说在之前状态加上一个路径j
 * - 当j>=d时，有dp[i+j][1]+=dp[i][0]——加上的路径j就可以满足1条件
 * - 任何时候，对于已经满足1条件的dp，都有dp[i+j][1]+=dp[i][1];
 * - 从短路i开始遍历，再遍历j，根据上述递推累加上情况数，dp[n][1]是解
 * - 每一步推到都没有问题，都从初始态推导得到了结果，合理性证明。 
 * 
 * 注意事项：
 * + 既然是有MOD的题目，为什么不多多模一模呢——输出个大数字多不好==
 * + 查了一下：这是一个有序完全背包问题。还需要学习。
 */
#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 1E9 + 7;
typedef long long longs;

int n,k,d;
longs dp[105][105];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k>>d;
    int lo=n-k,up=n-d;
    memset(dp,0,sizeof(dp));

    dp[0][0] = 1;
    for(int i=0;i<=n;++i)
        for(int j=1;j<=k;++j)
        {
            if(i+j>n)continue;
            if(j<d)
                dp[i+j][0]+=dp[i][0];
            else
                dp[i+j][1]+=dp[i][0];
            dp[i+j][1]+=dp[i][1];
            dp[i][0]%=MOD;
            dp[i][1]%=MOD;
        }
    cout<<dp[n][1]%MOD;

    return 0;
}