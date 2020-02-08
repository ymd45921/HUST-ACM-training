/**
 * 
 * 真尼玛快速幂啊？
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const char YES[] = "Yes";
const char NO[] = "No";
const longs MOD = 1e9+7;

int t;
int a,b,c,d,e,f,g;

longs fastpow(longs a ,longs b)
{
    if(!a) return 0==b;
    longs ans = 1;
    while(b)
    {
        if(b&1) ans = (ans*a)%MOD;
        a = (a*a)%MOD;
        b >>= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>t) while(t--)
    {
        cin>>a>>b>>c>>d>>e>>f>>g;
        longs tmp = fastpow(a,d) + fastpow(b,e) + fastpow(c,f);
        if(tmp == (longs)g) cout<<YES<<endl;
        else cout<<NO<<endl;
    }

    return 0;
}