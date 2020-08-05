#include <iostream>
#include <stack>

using namespace std;
typedef long long longs;
typedef bool boolean;

const longs MOD = 12345678910;
longs val[50005];

inline void preProcess()
{
    val[0] = 1;
    for(int i=1;i<=50001;++i)
        val[i] = (val[i-1]<<1)%MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();
    int n,in;
    while(cin>>n)
    {
        stack<bool> s;
        longs ans = 0;
        int mul = 0;
        boolean plus = false;
        for(int i=1;i<=n;++i)
        {
            cin>>in;
            if(in)
            {
                if(s.top())
                {
                    ans = (ans+val[mul])%MOD;
                    plus = false;
                }
                else --mul;
                s.pop();
            }
            else 
            {
                if(plus)
                {
                    s.pop();
                    s.push(false);
                    ++mul;
                }              
                else plus = true;
                s.push(true);
            }
        }
        cout<<ans<<endl;
    }

    return 0;
}