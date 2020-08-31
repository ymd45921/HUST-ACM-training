/**
 * 
 */
#include <iostream>
#include <cstring>

#define min(a,b) (a<b?a:b)

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
char s[200010];
int cnt1,cnt6;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        cin>>s;
        cnt1=cnt6=0;
        for(int i=0;i<n;++i)
            switch(s[i]-'0')
            {
            case 1:++cnt1;break;
            case 6:++cnt6;break;
            default:continue;
            }
        cout<<min(cnt1,cnt6-1)<<endl;
    }

    return 0;
}