/**
 *
 */
#include <iostream>
#include <string>
#include <queue>
#include <vector>

//#define mydebug

using namespace std;

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    string in,n,mstr;
    int m;
    size_t findpos;
    int digitlen;
    char ans[1050];

    while(getline(cin,in))
    {
        findpos = in.find(' ');
        mstr = in.substr(findpos+1);
        m = atoi(mstr.c_str());
        n = in.substr(0,findpos);
#ifdef mydebug
        cout<<"m = "<<m<<endl;
        cout<<"n = "<<n<<"\\0"<<endl<<endl;
#endif
        digitlen = n.length()-m;
        priority_queue<int,vector<int>,greater<int>> que;
        for(int i=0;i<=m;++i)
            que.push(n[i]-'0');
        for(int i=0;i<digitlen;++i)
        {
            ans[i] = que.top()+'0';
            que.pop();
            if(i==digitlen-1)break;
            que.push(n[m+i+1]-'0');
        }
        ans[digitlen] = 0;

        findpos = 0;
        while(ans[findpos]=='0')++findpos;
        if(ans[findpos]==0)--findpos;
        cout<<ans+findpos<<endl;
    }
    return 0;
}