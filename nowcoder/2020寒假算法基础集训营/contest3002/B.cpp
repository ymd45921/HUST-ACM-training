/**
 * 
 */
#include <iostream>
#include <iomanip>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,x,a,b;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<fixed<<setprecision(2);
    while(cin>>n>>x>>a>>b)
    {
        longd EX = (x*a+b*(100.0-x))/100.0;
        EX *= (longd)n;
        cout<<EX<<endl;
    }

    return 0;
}