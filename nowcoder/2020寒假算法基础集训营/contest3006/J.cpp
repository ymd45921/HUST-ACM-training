/**
 *
 * 我马上自杀，数学学的太差了
 * 
 * Passed的莫名其妙，浮点数少几把乘
 */
#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PIl          3.141592653589793238462643383279502884L

using namespace std;
typedef long long longs;
typedef long double longd;

int n,r,i,j;
longd ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout<<fixed<<setprecision(6);
    while(cin>>n>>r)
    {
        const longd theta = 2.0l*M_PIl/n;
        const longd length = r*sqrtl(2.0l - 2.0l*cosl(theta));
        cin>>i>>j;
        if(i>j)swap(i,j);
        if(j-i>(n>>1)) ans = length*(n-j+i);
        else ans = length*(j-i);
        cout<<ans<<endl;
    }

    return 0;
}