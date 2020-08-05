/**
 *
 * 通过了两个样例，为什么还是有什么没考虑到？
 * 也排除了极端情况的问题，为什么不对呢==
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;

const int MOD = 1000000007;

int n,m;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        longs ans = 0;
        longs tmp = (m-2)*(n-1)%MOD;
        ans += (tmp*2*m)%MOD;
        ans %= MOD;
        tmp = (n-2)*(m-1);
        ans += (tmp*2*n)%MOD;
        ans %= MOD;
        tmp = (m-2)*(n-2)%MOD;
        ans += (tmp*2*(m-1))%MOD;
        ans %= MOD;
        ans += (tmp*2*(n-1))%MOD;
        ans %= MOD;
        if(ans<0)ans+=MOD;
        cout<<ans<<endl;
    }

    return 0;
}