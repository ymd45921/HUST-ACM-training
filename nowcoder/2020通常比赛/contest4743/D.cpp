/**
 *
 * 1 2 3 4 找规律？
 * 1e18
 *
 * 怎么试探性的找规律害T了？
 */
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;

const int N = 100;
const int M = 64;

longs st[N], ed[N];

void preProcess()
{
    st[0] = ed[0] = 1;
    for(int i = 1; i <= M; ++i)
    {
        st[i] = ed[i-1] + 1;
        ed[i] = (ed[i-1]<<1) + (i&1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();

    int t;
    longs n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int s = upper_bound(st,st+M,n) - st;
        if(s&1) cout<<"XiaoQiao"<<endl;
        else cout<<"XiaoHuiHui"<<endl;
    }

    return 0;
}