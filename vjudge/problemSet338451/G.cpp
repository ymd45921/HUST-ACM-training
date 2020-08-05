#include <iostream>
#include <cstring>

using namespace std;

int n,a[150050],in;
int ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(a,0,sizeof(a));
    a[0] = 1;
    cin>>n;
    for(int i=0;i<n;++i)
    {
        cin>>in;
        ++a[in];
    }
    for(int i=1;i<150002;++i)
    {
        if(!a[i]&&a[i+1])
        {
            a[i+1]--;
            a[i]++;
            ++ans;
        }
        else if(a[i])
        {
            ++ans;
            if(a[i]>1)a[i+1]++;
        }
    }
    cout<<ans;
    return 0;
}

