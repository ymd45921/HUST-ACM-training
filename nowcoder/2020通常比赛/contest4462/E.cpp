/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    longs n,m,r,c;
    while(cin>>n>>m>>r>>c)
    {
        longs nm = n*m;
        cout<<(nm-r*m-c*n+r*c)<<endl;
    }

    return 0;
}