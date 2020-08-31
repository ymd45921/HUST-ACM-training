/**
 *
 * next你的妈
 * 爬爬法就可以了
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,k;
char str[1000010];
int cnt[30]{0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        cin>>str;
        int ans = 0x3f3f3f3f;
        memset(cnt,0,sizeof(cnt));
        int head = 0,tail = 0;

        while(head<n)
        {
            if(++cnt[str[head]-'a']>=k)
            {
                while(str[tail]!=str[head]||cnt[str[tail]-'a']>k)
                    --cnt[str[tail++]-'a'];
                if(head-tail+1<ans)ans = head-tail+1;
            }
            ++head;
        }
        if(ans==0x3f3f3f3f)ans = -1;

        cout<<ans<<endl;
    }

    return 0;
}