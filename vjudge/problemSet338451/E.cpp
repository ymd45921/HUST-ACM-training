#include <iostream>
#include <cstring>

#define mst(x) memset(x,0,sizeof(x))
#define max(x,y) (x>y?x:y)

using namespace std;
int c;
char s[105],t[105];
int cnt[5],ans;                                     //0:^?-v0; 1:^?-v1; 2:^1-v0; 3:^0-v1;             

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>c;
    int caseNum = 0;

    while(c--)
    {
        cin>>s>>t;
        int len = strlen(s);
        mst(cnt);
        
        for(int i=0;i<len;++i)
        {
            if(s[i]=='?')
                ++cnt[t[i]-'0'];
            else if(s[i]!=t[i])
                ++cnt[t[i]-'0'+2];    
        }

        if(cnt[2]>cnt[1]+cnt[3])ans = -1;
        else
        {
            ans = cnt[0]+cnt[1]+max(cnt[2],cnt[3]);
        }
        
        cout<<"Case "<<++caseNum<<": "<<ans;
        cout<<endl;
    }

    return 0;
}