#include <iostream>
#include <cstring>

#define mst(x) memset(x,0,sizeof(x))

using namespace std;
int c;
char s[105],t[105];
int mov[5];             //[change0to1,change1to0,change?to0,change?to1,swap]
int ans;                //可能性：[1,1,(0,1),1,2]

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
        mst(mov);
        for(int i=0;i<len;++i)
        {
            if(s[i]=='?')++mov[2+t[i]-'0'];
            else if(s[i]!=t[i])mov[s[i]-'0']++;
        }
        if(mov[1]>mov[0]+mov[3])ans = -1;
        else ans = mov[0]>mov[1]?mov[0]:mov[1]+mov[2]+mov[3];
        cout<<"Case "<<++caseNum<<": "<<ans;
        if(c)cout<<endl;
    }

    return 0;
}