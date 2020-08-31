/**
 * 
 * 不对不对，不是这样的
 * 
 * 可以双指针，考虑每一个数字对应的可选择区间。
 * 但是这样只能得到每个位置可以填入的数字
 * 然后把它们乘起来就好了
 * 
 * ……虽说也能猜到是乘起来。
 * 我日他让你求全排列不让你求操作方案数
 * 那不就必然是乘嘛我操血亏
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

    while(cin>>n)
    {
        for(int i=1;i<=n;++i) cin>>a[i];
        for(int i=1;i<=n;++i) cin>>b[i];
        sort(a+1,a+1+n);sort(b+1,b+1+n);
        a[0]=b[0]=-1;
        a[n+1]=b[n+1]=0x7fffffff;

        int ca=1,cb=1;
        longs ans = 1;
        for(;ca<=n;++ca)
        {
            while(cb<=n&&a[cb]<=b[ca])++cb;
            ans = ans*max((longs)cb-ca,0ll)%mod;
        }
        cout<<(ans+mod)%mod<<endl;
    }

    return 0;
}