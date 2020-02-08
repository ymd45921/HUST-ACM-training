/**
 * 
 */
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,k;
int a[300050];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        for(int i=0;i<n;++i) cin>>a[i];
        sort(a,a+n);
        int ans = 0;
        
        

        cout<<ans<<endl;
    }

    return 0;
}