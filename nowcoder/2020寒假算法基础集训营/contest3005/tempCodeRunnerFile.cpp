/**
 * 
 * 果然不是简单的2*a+b…………
 */
#include <iostream>

#define A 0
#define B 1

using namespace std;
typedef long long longs;
typedef long double longd;

int t,n,ans;
int dp[2][100];

inline void preProcess()
{
    dp[A][0] = 1;
    dp[B][0] = 0;
    dp[A][1] = 2;
    dp[B][1] = 1;
    for(int i=2;i<100;++i)
    {
        dp[B][i] = dp[A][i-1];
        dp[A][i] = dp[A][i-1]+dp[B][i-1];
    }
}

inline int getAnswer(int n)
{
    return dp[A][n]+dp[B][n];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();

    while(cin>>t)
    {
        while(t--)
        {
            cin>>n;
            ans = getAnswer(n);
            cout<<ans<<endl;
        }
    }

    return 0;
}