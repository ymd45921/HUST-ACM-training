/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,in;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        longs ans = ((1+n)<<1)*n;
        for(int i=1;i<n;++i)
        {
            cin>>in;
            ans-=in;
        }
        cout<<ans;
    }

    return 0;
}