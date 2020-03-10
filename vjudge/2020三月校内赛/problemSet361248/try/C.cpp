/**
 * 
 * 解方程
 * 
 * 还可以binary Search
 * 
 */

#include <iostream>
#include <cstdio>
#include <iomanip>

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout<<fixed<<setprecision(9);

    longs x,y;
    cin>>x>>y;
    int n;
    cin>>n;
    longd sum = 0, k;
    longs u,l, d = 0;
    while(n--)
    {
        cin>>l>>u>>k;
        d += u-l;
        sum += k*(u-l);
    }
    longd ans = x/(y-d+sum);
    cout<<ans<<endl;

    return 0;
}