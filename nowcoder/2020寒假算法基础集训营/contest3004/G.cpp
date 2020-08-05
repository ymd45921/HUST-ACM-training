/**
 * 
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 1e9+7;

int n,m,q,pos;;
char ch[100010];
longs pre[100010];
longs sum,cnt;
longs ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(pre,0,sizeof(longs)*n);
        cin>>ch;
        sum = cnt = 0;
        ans = 0;
        cin>>m;

        for(int i=0;i<n;++i)
        if(ch[i]=='1')
        {
            ans += cnt*i-sum;
            sum += i;
            ++cnt;
            ans %= MOD;
        }
        cout<<ans<<endl;

        while(m--)
        {
            cin>>q>>pos;
            switch(q)
            {
            case 1:

            case 2:

            default:break;
            }
        }
    }

    return 0;
}