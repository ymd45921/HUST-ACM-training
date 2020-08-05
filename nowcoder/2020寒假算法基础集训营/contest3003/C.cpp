/**
 * 
 * 分数取模后一些运算还是符合的，所以不用在意便是
 * 
 * 怎么害通过率50%的（）
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs modl = 1e9 + 7;
const int modi = 1e9 + 7;

int n;
int p[2080];
longs ans[2080][2080]{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        for(int i=1;i<=n;++i)
        {
            cin>>p[i];
        }

        ans[0][0] = 1;
        for(int i=1;i<=n;++i)
        {
            ans[i][0] = (modl+1-p[i])%modl*ans[i-1][0]%modl;
            for(int j=1;j<=i;++j)
            {
                ans[i][j] = ans[i-1][j-1]*(p[i])%modl + ans[i-1][j]*(modl+1-p[i])%modl;
                ans[i][j] %= modl;  // 害，忘记除模了
            }
        }
        for(int i=0;i<=n;++i)
            cout<<ans[n][i]<<' ';
        cout<<endl;
    }

    return 0;
}