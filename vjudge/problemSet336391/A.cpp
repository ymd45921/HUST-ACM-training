#include <iostream>
#include <cstring>
#define MEMSET0(x) memset(x,0,sizeof(x))

using namespace std;

int N,n;
int theQue[5005];
int theNext[5005];
int ans[50050][3];

inline void cut2(int& length)
{
    int lim = length/2;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur] = theNext[theNext[cur]];
        --length;
    }
}

inline void cut3(int& length)
{
    int lim = length/3;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur];
        cur = theNext[cur] = theNext[theNext[cur]];
        --length;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    theNext[0]=0;
    MEMSET0(ans);

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        MEMSET0(theNext);
        MEMSET0(theQue);
        if(n<=3)
        {
            int cur = 0;
            int x = 1;
            while(x<=n)
            {
                ans[i][cur]=x;
                ++cur;
                ++x;
            }
        }
        else if(n-(n>>1)<=3)
        {
            int x = 1;
            int cur = 0;
            while(x<=n)
            {
                ans[i][cur] = x;
                ++cur;
                x+=2;
            }
        }
        else
        {
            int x = 1,cur = 1;
            while(x<=n)
            {
                theQue[cur]=x;
                theNext[cur]=cur+1;
                ++cur;
                x+=2;
            }
            theNext[--cur]=-1;
            int flag = 1;
            int length = n-(n>>1);
            while(length>3)
            {
                if(flag)cut3(length);
                else cut2(length);
                flag^=1;
            }
            ans[i][0] = theQue[1];
            ans[i][1] = theQue[theNext[1]];
            ans[i][2] = theQue[theNext[theNext[1]]];
        }
    }

    int lim = N-1;
    for(int i=0;i<lim;++i)
    {
        cout<<ans[i][0];
        if(ans[i][1])cout<<' '<<ans[i][1];
        if(ans[i][2])cout<<' '<<ans[i][2];
        cout<<endl;
    }
    cout<<ans[lim][0];
    if(ans[lim][1])cout<<' '<<ans[lim][1];
    if(ans[lim][2])cout<<' '<<ans[lim][2];
    cout<<endl;

    return 0;
}