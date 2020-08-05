/**
 * 
 * 1e9 不太敢dp
 * 
 * 典型的线性规划不稳健，还可以三分
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long longs;

// longs dp(longs x, longs y)
// {
//     longs xx = ((y<<2)-x)/10;
//     longs yy = y - 3*xx;
//     return xx+yy;
// }

int x,y;

longs check(longs m)
{
    longs n = min((x-(m<<1))>>2, y-3*m);
    return m+n;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;
        
        int l = 0;
        int r = max(min(x/2,y/3),min(x/4,y));
        while(r-l>10)
        {
            int t = (r-l)/3;
            int m1 = l+t, m2 = r-t;
            if(check(m1) > check(m2)) r = m2;
            else l = m1;
        }
        longs ans = 0;
        for(int i=l;i<=r;++i)
            ans = max(ans,check(i));
        cout<<ans<<endl;
    }

    return 0;
}