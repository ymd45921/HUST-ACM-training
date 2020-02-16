/**
 *
 */
#include <iostream>
#include <cmath>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs LLMAX = 0x7fffffffffffffffll;
int t;
longs n;

bool is[1000100]{0};
int prime[1000100]{0};

inline void preProcess()
{
    int tmp;
    for(int i=2;i<=1000010;++i)
    {
        if(!is[i]) prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&(tmp=i*prime[j])<=1000010;++j)
        {
            is[tmp]=1;
            if(i%prime[j]==0)break;
        }
    }
}

inline longs solve(longs n)
{
    if(!(n&1ll))
    {
        int cnt = 0;
        while(!(n&1ll))
        {
            ++cnt;
            n>>=1;
        }
        return (1ll<<(cnt/3))*solve(n);
    }
    longs clim = pow(n,1.0l/3.0l);
    if(!(clim&1ll)) clim-=1;
    longs c,c3 = clim*clim*clim;
    if(n%c3);else return clim;
    // for(c=3;c<=clim&&c<8;c+=2)
    //     if(n%c) continue;
    //     else
    //     {
    //         c3 = c*c*c;
    //         if(n%c3) return solve(n/c);
    //         else return c*solve(n/c3);
    //     }
    // for(c=11;c<=clim;c+=2)
    //     if(n%c) continue;
    //     else
    //     {
    //         c3 = c*c*c;
    //         if(n%c3) return solve(n/c);
    //         else return c*solve(n/c3);
    //     }
    for(int i=1;i<=prime[0]&&prime[i]<=clim;++i)
        if(n%prime[i]) continue;
        else
        {
            c3 = prime[i]*prime[i]*prime[i];
            if(n%c3) return solve(n/prime[i]);
            else return prime[i]*solve(n/c3);
        }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    preProcess();
    while(t--)
    {
        cin>>n;
        cout<<solve(n)<<endl;
    }

    return 0;
}