/* 
 * 采用逆推的dp方法，设dp[i]是从i开始选择的最大收益：
 * 则，dp[i] = max(dp[i+1], {suffixSum[i+1]-dp[i+1]}+a[i]);
 * 情况1：放弃这次的数字，得到之后能获得的最大数——放弃a[i]；
 * 情况2：获得这个数字，在对面获得最优解的情况下获得剩下的所有数；
 * 实际上，dp[i]是任何人从i开始选择可以得到的最大数字。
 * 然后呢，这个题目，谁先手，谁就能取得dp[0]——因为dp就是这么定义的==
 */
#include <iostream>
#include <cstring>

#define max(a,b) (a>b?a:b)

using namespace std;

int n,a[60];
int alice,bob;
int suffixSum[60];
int dp[60],odp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=0;i<n;++i)cin>>a[i];
    alice = bob = 0;
    suffixSum[n] = 0;
    odp = dp[n] = 0;

    for(int i=n-1;i>=0;--i)
    {
        suffixSum[i]=suffixSum[i+1]+a[i];
        dp[i] = max(dp[i+1],odp+a[i]);
        odp = suffixSum[i]-dp[i];
    }

    cout<<odp<<' '<<dp[0];
    return 0;
}