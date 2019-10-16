#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;

int n,k,m;
int a[100005];
longs sum = 0;
int resi,oper;
long double ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k>>m;
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        sum+=a[i];
    }
    sort(a,a+n);
    resi = n;

}