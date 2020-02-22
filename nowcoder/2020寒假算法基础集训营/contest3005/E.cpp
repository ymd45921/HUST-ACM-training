/**
 * 
 * 无他，就是那样贪心。就是实现注意一下
 * 
 * WA原因：高精度，不然装不下
 * 要打高精度真就小心再小心啊
 * 
 * 仔细想想就算想出了贪心，但是能改进的地方还是很多……
 * 比如不用一个个加上去这种（）但是要损失别的==
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>

#define ch in[i]

using namespace std;
typedef long long longs;
typedef long double longd;

char in[500050];
int cnt[11];
int ans[500050];

inline int solution()
{
    const int num = cnt[10]+1;
    memset(ans,0,sizeof(ans));
    int c = 0,n = 0;
    for(int i=9;i>0;--i)
        while(cnt[i])
        {
            ans[n] += i;
            --cnt[i];
            c = (c+1)%num;
            if(!c) ++n;
        }
    for(int i=0;i<=n;++i)
    {
        ans[i+1] += ans[i]/10;
        ans[i] %= 10;
    }
    for(int i=n+1;ans[i];++i)
    {
        ans[i+1] += ans[i]/10;
        ans[i] %= 10;
        n = i;
    }
    while(!ans[n])--n;
    return n;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>in)
    {
        memset(cnt,0,sizeof(cnt));
        const int len = strlen(in);
        for(int i=0;i<len;++i)
        {
            if(ch=='+')++cnt[10];
            else ++cnt[ch-'0'];
        }
        int alen = solution();
        for(int i=alen;i>=0;--i)
            cout<<ans[i];
        cout<<endl;
    }

    return 0;
}