/**
 * 
 * 要longs就longs到底，要不然就强制转换
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 1e9+7;

int n;
char ch[100010];
longs sum,cnt;
longs ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        cin>>ch;
        sum = cnt = 0;
        ans = 0;

        for(int i=0;i<n;++i)
        if(ch[i]=='1')
        {
            ans += cnt*i-sum;
            sum += i;
            ++cnt;
            ans %= MOD;
        }
        cout<<ans<<endl;
    }

    return 0;
}