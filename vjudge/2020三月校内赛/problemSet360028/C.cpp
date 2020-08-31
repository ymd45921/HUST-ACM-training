/**
 * 
 * WA: -2
 */
#include <iostream>

using namespace std;
typedef long long longs;

int n,d[400];
const int lim = 20;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        int ans = 0;
        int dt = 0;
        int push = 0;
        for(int i=1;i<=n;++i)
        {
            cin>>d[i];
            if(push)
            {
                dt += push*(d[i]-d[i-1]);
                if(dt>=lim)
                {
                    push = dt = 0;
                    ++ans;
                }
            }
            ++push;
        }
        if(push)
        {
            dt += push*(366-d[n]);          //366:关键的一步
            if(dt) ++ans;
        }
        cout<<ans<<endl;
    }

    return 0;
}