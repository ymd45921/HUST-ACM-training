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
    for(c=3;c<=clim&&c<8;c+=2)
        if(n%c) continue;
        else 
        {
            c3 = c*c*c;
            if(n%c3) return solve(n/c);
            else return c*solve(n/c3);
        }
    for(c=11;c<=clim;c+=2)
        if(n%c) continue;
        else
        {
            c3 = c*c*c;
            if(n%c3) return solve(n/c);
            else return c*solve(n/c3);
        }
    return 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<solve(n)<<endl;
    }

    return 0;
}