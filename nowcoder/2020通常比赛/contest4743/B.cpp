#include <iostream>
#include <cstdlib>
#include <algorithm>

#define fee(a,b) (abs(f[a]-f[b]))

using namespace std;
typedef long long longs;

const int N = 1e5+5;

int n;
longs f[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    longs x,y;
    for(int i = 1; i <= n; ++ i)
    {
        cin>>x>>y;
        f[i] = y*(x-y)*(x-y);
    }
    sort(f+1,f+1+n);
    longs ans = 0;
    for(int i = 1; i < n; ++ i)
        ans += f[i+1]-f[i];
    cout<<ans;

    return 0;
}