#include <iostream>
#include <cstring>

using namespace std;
int n,in;
int ans[10];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(ans,0,sizeof(ans));
        for(int i=0;i<n;++i)
        {
            cin>>in;
            ans[0]+=in/100;
            in%=100;
            ans[1]+=in/50;
            in%=50;
            ans[2]+=in/20;
            in%=20;
            ans[3]+=in/10;
            in%=10;
            ans[4]+=in/5;
            in%=5;
            ans[5]+=in;
        }
        cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2]<<' '
            <<ans[3]<<' '<<ans[4]<<' '<<ans[5]<<endl;
    }

    return 0;
}