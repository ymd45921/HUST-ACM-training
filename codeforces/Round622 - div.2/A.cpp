#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t,a,b,c;
    cin>>t;
    while(t--)
    {
        cin>>a>>b>>c;
        int ans = 0;
        if(a>0)++ans,--a;
        if(b>0)++ans,--b;
        if(c>0)++ans,--c;  
        int ar[3] = {a,b,c};
        sort(ar,ar+3);
        if(ar[2]>0&&ar[1]>0)
        {
            --ar[2];
            --ar[1];
            ++ans;
        }
        if(ar[2]>0&&ar[0]>0)
        {
            --ar[2];
            --ar[0];
            ++ans;
        }
        if(ar[1]>0&&ar[0]>0)
        {
            --ar[1];
            --ar[0];
            ++ans;
        }
        a=ar[0];b=ar[1];c=ar[2];
        if(a>0&&b>0&&c>0)++ans;
        cout<<ans<<endl;
    }

    return 0;
}