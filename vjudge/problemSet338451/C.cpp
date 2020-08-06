#include <iostream>
#include <algorithm>

using namespace std;
int n,b[1050];
long long ans;
// int sum[1050];

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    while(cin>>n)
    {
        ans = 0;
        for(int i=0;i<n;++i) cin>>b[i];
        sort(b,b+n);
        // sum[0] = 0;
        // for(int i=1;i<=n;++i) sum[i]=sum[i-1]+b[i-1];
        for(int i=0;i<n;++i)
            ans += b[i]*(n-i);
        cout<<ans<<endl;
    }

    return 0;
}