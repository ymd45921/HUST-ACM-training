#include <iostream>
#include <algorithm>

using namespace std;

int t,n,s;
int in[100050];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;

    while(t--)
    {
        cin>>n;
        cin>>s;
        for(int i=0;i<n;++i)
            cin>>in[i];
        
        int ans = 0;
        sort(in,in+n);
        int cur = 0, rcur = n-1;
        int residue = n;
        while(residue>0)
        {
            if(cur>=rcur)break;
            if(in[cur]+in[rcur]<=s)
            {
                ++ans;
                residue-=2;
                ++cur;
                --rcur;
            }
            else
            {
                ++ans;
                --residue;
                --rcur;
            }
        }
        if(residue)++ans;
        cout<<ans<<endl;
        if(t)cout<<endl;
    }
}