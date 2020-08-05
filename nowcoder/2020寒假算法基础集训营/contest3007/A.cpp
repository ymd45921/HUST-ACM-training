/**
 * 
 */
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,k;
int a[100010],b[100010];
int ans[100010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        for(int i=0;i<n;++i) cin>>a[i];
        for(int i=0;i<n;++i) cin>>b[i];
        sort(a,a+n); sort(b,b+n);
        for(int i=n-k,j=n-1,x=0;i<n;++i,--j,++x)
            ans[x] = a[i]+b[j];
        sort(ans,ans+k);
        cout<<ans[0]<<endl;
    }

    return 0;
}