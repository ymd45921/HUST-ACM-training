/**
 *
 */
#include <iostream>
#include <cmath>

#define max(a,b) (a>b?a:b)

using namespace std;

int n,k;
int a[2060];

inline int c(const int a[], int n)
{
    if(n<=1&&n>=0)return 0;
    int ans = 0;
    for(int i=1,j=2;j<=n;++i,++j)
        ans = max(ans,abs(a[j]-a[i]));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];

    return 0;
}