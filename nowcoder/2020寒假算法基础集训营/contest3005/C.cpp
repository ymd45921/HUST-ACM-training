/**
 * 
 * MOD是质数
 * 虽说有同余的问题，还有MOD数变换的问题
 */
#include <iostream>

#define mylog

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 998244353;

int a[200020];
int n,k;
longs ans,tmp;
int zero;

inline longs gcdMODand(longs n)
{
    if(n==MOD) return MOD;
    else return 1ll;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        ans = 0;
        tmp = 1;
        zero = 0;
        for(int i=0;i<k;++i)
        {
            cin>>a[i];
            if(a[i])tmp=(a[i]*tmp)%MOD;
            else ++zero;
        }
    #ifdef mylog
        cout<<"[0,"<<k-1<<"] = "<<(zero?0:tmp)<<endl;
    #endif
        ans = zero?0:tmp;
        for(int i=k;i<n;++i)
        {
            cin>>a[i];
            if(a[i])tmp=(a[i]*tmp)%MOD;
            else ++zero;
            if(a[i-k])tmp=(tmp/a[i-k])%MOD;
            else --zero;
    #ifdef mylog
        cout<<"["<<i-k+1<<","<<i<<"] = "<<(zero?0:tmp)<<endl;
    #endif
            ans = ans>(zero?0:tmp)?ans:(zero?0:tmp);
        }
        cout<<ans<<endl;
    }

    return 0;
}