/**
 * 
 */
#include <iostream>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

using namespace std;
typedef long long longs;
typedef long double longd;

int a,b,c,x,y,z;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>a>>b>>c>>x>>y>>z)
    {
        longs ans = 0;
        ans += min(a,y);
        ans += min(b,z);
        ans += min(c,x);

        cout<<ans<<endl;
    }

    return 0;
}