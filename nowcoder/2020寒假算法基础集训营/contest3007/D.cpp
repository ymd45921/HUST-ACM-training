/**
 * 
 * 不对不对，不是这样的
 */
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs mod = 1e9+7;

int n;
int a[100010],b[100010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=n;++i) cin>>b[i];
    sort(a+1,a+1+n);sort(b+1,b+1+n);
    a[0]=b[0]=-1;
    a[n+1]=b[n+1]=0x7fffffff;

    int ca=1,cb=1;
    longs ans = 0;
    for(;ca<=n&&cb<=n;++ca)
    {
        if(a[ca]==a[ca-1])
        {
            ans=(ans+cb-ca-1)%mod;
            continue;
        }
        while(b[cb]<=a[ca])++cb;
        ans=(ans+cb-ca-1)%mod;
    }

    return 0;
}