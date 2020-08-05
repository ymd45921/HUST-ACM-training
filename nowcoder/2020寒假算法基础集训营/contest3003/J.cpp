/**
 * 
 * 直接模拟会TLE。
 * 
 * 题解：这题需要线段树
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;
struct poly 
{
    int k,b; 
    int f(longs x);
};

const int MOD = 1e9+7;
int n,m,tmp;
poly in[200050];
int t,i,k,b,l,r;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        for(int i=1;i<=n;++i)cin>>in[i].k;
        for(int i=1;i<=n;++i)cin>>in[i].b;
        while(m--)
        {
            cin>>t;
            switch(t)
            {
            case 1:cin>>i>>k>>b;
                in[i] = {k,b};
                break;
            case 2:cin>>l>>r;
                tmp = 1;
                for(int i=l;i<=r;++i)
                    tmp = in[i].f(tmp);
                cout<<tmp<<endl;
                break;
            default:break;
            }
        }
    }

    return 0;
}

int poly::f(longs x)
{
    longs ans = k*x+b;
    return (int)(ans%MOD);
}