/**
 *
 * 搞一个 W = ⁴√n 是真的没有看懂==
 */
#include <iostream>
#include <cmath>

using namespace std;
typedef long long longs;
typedef long double longd;

int t;
longs n;

bool is[1000100]{0};
int prime[100000]{0};           // 1e6内质数大约是7.2w个
longs tri[100000],qua[1000000];

inline void preProcess()        // 欧拉筛 + 预先计算幂
{
    int tmp;
    for(int i=2;i<=1000010;++i)
    {
        if(!is[i]) 
        {
            prime[++prime[0]]=i;
            tri[prime[0]] = i*i*i;
            qua[prime[0]] = tri[prime[0]]*i;
        }
        for(int j=1;j<=prime[0]&&(tmp=i*prime[j])<=1000010;++j)
        {
            is[tmp]=1;
            if(i%prime[j]==0) break;
        }
    }
}

inline longs solve(longs n)
{
    if(!(n&1ll))                // 处理因数2
    {
        int cnt = 0;
        while(!(n&1ll))
        {
            ++cnt;
            n>>=1;
        }
        return (1ll<<(cnt/3))*solve(n);
    }
    longs ans = 1;
    for(int i=1;qua[i]<=n;++i)  // i<=prime[0]没有必要
        if(n%prime[i]) continue;
        else                    // 完全去除这个因数
        {
            while(!(n%tri[i]))
            {
                ans *= prime[i];
                n /= tri[i];
            }
            while(!(n%prime[i])) n/=prime[i];
        }
    int lb = 1, rb = 1000000;
    while(lb<=rb)               // 可以二分查找
    {
        int mid = lb+rb >> 1;
        if((longs)mid*mid*mid<n) lb = mid+1;
        else rb = mid-1;
    }
    if((longs)lb*lb*lb==n) ans*=lb;
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();
    while(cin>>t)
    while(t--)
        {
            cin>>n;
            cout<<solve(n)<<endl;
        }

    return 0;
}