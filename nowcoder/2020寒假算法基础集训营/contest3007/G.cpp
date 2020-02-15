/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int t,n;
int stack;
char in;
int ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>t)
    {
        while(t--)
        {
            cin>>n;
            stack = ans = 0;
            for(int i=1;i<=n;++i)
            {
                cin>>in;
                if(in=='(') ++stack;
                else if(!stack)++ans;
                else --stack;
            }
            ans+=stack;
            cout<<ans<<endl;
        }
    }

    return 0;
}