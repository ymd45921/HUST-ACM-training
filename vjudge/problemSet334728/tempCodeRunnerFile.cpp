#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;
typedef long long longs;
typedef long double doubles;

int n,k,m;
int a[100005];
longs sum[100005] = {0};
doubles ans;

doubles getAnswer(int i)
{
    int deleted = n-i;
    int added = k*i<m-deleted?k*i:m-deleted;
    return ((double)sum[deleted]+(double)added)/(double)i;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k>>m;
    cin>>a[0];
    for(int i=1;i<n;++i) cin>>a[i];
    sort(a,a+n);
    sum[n-1] = a[n-1];
    for(int i=n-2;i>=0;--i) sum[i] = sum[i+1]+a[i];

    int lbound = 1>(n-m)?1:(n-m);
    int rbound = n;
    doubles ans1,ans2;
    int cp1,cp2,dev;
    while(lbound<=rbound)
    {
        dev = (rbound-lbound)/3;
        cp1 = lbound+dev;
        cp2 = rbound-dev;
        ans1 = getAnswer(cp1);
        ans2 = getAnswer(cp2);
        if(ans1>ans2)
        {
            ans = ans1;
            rbound = cp2-1;
        }
        else
        {
            ans = ans2;
            lbound = cp1+1;
        }
    }

    cout<<fixed<<setprecision(20);
    cout<<ans;
    return 0;
}