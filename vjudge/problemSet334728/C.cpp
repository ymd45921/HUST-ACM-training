#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long longs;

int*a,*q;
int n,m;
longs sum = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    a = new int[n];
    for(int i=0;i<n;++i)
    {
        cin>>a[i];
        sum+=a[i];
    }
    sort(a,a+n);
    cin>>m;
    q = new int[m];
    for(int i=0;i<m;++i)
    {
        cin>>q[i];
        cout<<sum-a[n-q[i]]<<endl;
    }

    return 0;
}