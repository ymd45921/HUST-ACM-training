#include <iostream>
#include <algorithm>

#define getN(m) min(y-3*(m),(x-2*(m))>>2)

using namespace std;
typedef long long longs;

longs solve(int x, int y)
{
    longs m = (4ll*y-x)/10ll;
    longs n = getN(m);
    if(m <= 0 || n <= 0)
        return max(min(x>>1,y/3),min(x>>2,y));
    longs ans = max(m+n,m+1+getN(m+1));
    return max(ans,m-1+getN(m-1));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    longs t,x,y;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;
        cout<<solve(x,y)<<endl;
    }

    return 0;
}