/**
 * 
 * 果然不是简单的2*a+b…………
 * 
 * 孩他妈能找规律？
 * 
 * 就尼玛离谱，我也是fib数列啊==
 * 
 * 就尼玛离谱，非要我复制标程？
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int t,n,ans;
longs fib[125];

inline void preProcess()
{
    fib[0] = 1;
    fib[1] = 2;
    for(int i=2;i<=120;++i)
    fib[i] = fib[i-1]+fib[i-2];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();

    while(cin>>t)
    {
        while(t--)
        {
            cin>>n;
            if(n == 0)cout<<1<<endl;
            else cout<<fib[n]+fib[n-1]<<endl;
        }
    }

    return 0;
}