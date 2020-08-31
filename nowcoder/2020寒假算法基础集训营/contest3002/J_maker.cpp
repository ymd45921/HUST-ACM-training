#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

longs fib[100000000] = {0};
const int MOD = 1000000007;

longs ffib(int x)
{
    if(x<=0) return x;
    if(!fib[x])
        return fib[x] = ffib(x-1) + ffib(x-2);
    else return fib[x];
}

int fastpow(longs a,longs b)
{
    longs ans = 1;
    while(b)
    {
        if(b&1) ans = (ans*a)%MOD;
        a = (a*a)%MOD;
        b>>=1;
    }
    return ans%MOD;
}

int main()
{
    fib[1] = fib[2] = 1;
    int n,x,y,a,b,c;

    while(cin>>n>>x>>y>>a>>b)
    {
        c = fastpow(a,b);
        cout<<"fastpow: c = "<<a<<'^'<<b<<" = "<<c<<endl;
        longs ans = 1;
        longs tmp = fastpow(c,ffib(n)-1);
        cout<<"ffib: "<<"{ "<<fib[n]<<", "<<fib[n-1]<<", "<<fib[n-2]<<" }\n";
        cout<<"Temp: "<<"c^(fib(n)-1) = "<<tmp<<endl;
        ans *= tmp%MOD;
        tmp = fastpow(x,ffib(n-2));
        cout<<"Temp: "<<"x^(fib(n-2)) = "<<tmp<<endl;
        ans *= tmp%MOD;
        ans %= MOD;
        tmp = fastpow(y,ffib(n-1));
        cout<<"Temp: "<<"y^(fib(n-1)) = "<<tmp<<endl;
        ans *= tmp%MOD;
        ans %= MOD;
        cout<<ans<<endl;
    }

    return 0;
}