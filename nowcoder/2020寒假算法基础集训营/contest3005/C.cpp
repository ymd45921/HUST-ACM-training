/**
 * 
 * MOD是质数
 * 虽说有同余的问题，还有MOD数变换的问题
 * 
 * 可以使用线段树，也可以分治，还可以使用尺取法，维护当前区间中有几个0，同时维护不是0的数字的乘积，这种方法需要使用乘法逆元。
 * 我也这么觉得啊？？
 * 难道问题在MOD变换上？
 * 
 * 果然，用上了费马小定理之后就AC了
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 998244353;
const longs POW = MOD-2;

int a[200020];
int n,k;
longs ans,tmp;
int zero;

int mod(longs a, longs b)
{
    if(!b) return -1;
    longs ans = 1;
    int n = POW;
    while(n)
    {
        if(n&1) ans = (ans*b)%MOD;
        b = (b*b)%MOD;
        n >>= 1;
    }
    ans = (ans*a)%MOD;
    return int(ans);
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
            if(a[i-k])tmp=mod(tmp,a[i-k]);
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