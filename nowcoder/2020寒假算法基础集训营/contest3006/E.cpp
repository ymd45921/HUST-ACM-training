/**
 * 
 * 判断后手能不能赢
 * 
 * 持有方到2,4必输
 * 1<<k情况下必输
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const char Yes[] = "Bob";
const char No[] = "Alice";

longs n;

bool onlyOneBit(longs ll)
{
    int cnt = 0;
    for(int i=1;i<=63;++i)
    {
        if((1ll<<i)&ll)++cnt;
    }
    if(cnt==1)return true;
    else return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        if(n&1ll) cout<<Yes<<endl;
        else if(onlyOneBit(n))cout<<No<<endl;
        else cout<<Yes<<endl;
    }
    return 0;
}