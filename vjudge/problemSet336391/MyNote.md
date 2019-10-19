# HUST-ACM 2019新生B class训练题

专题：数据结构基础 日期：2019-10-19

## Problem A

为什么我总是感觉这个题目有约瑟夫环式的递推公式？

**Version 1** : 没有正确性的瞎jb优化
```c++
#include <iostream>
#include <cstring>

using namespace std;

int N,n;
int theQue[5005];
int theNext[5005];

inline void cut2(int& length)
{
    int lim = length/2;
    int cur = 1;
    for(int i=0;i<lim;++i)
    {
        cur = theNext[cur] = theNext[theNext[cur]];
        if(--length==3)return;
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
        if(--length==3)return;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    theNext[0]=0;

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        if(n<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x++;
            }
            cout<<endl;
        }
        else if(n-(n>>1)<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x+=2;
            }
            cout<<endl;
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
            cout<<theQue[1]<<' '<<theQue[theNext[1]]<<' '<<theQue[theNext[theNext[1]]]<<endl;
        }
    }

    return 0;
}
```
错误分析：应该是数组指针没指对地方==改了一下，这个版本应该不至于WA了吧。不对，还是WA了==
查了一下，好像又是个语文题？

**Version 2** : Presentation Error.
```c++
#include <iostream>
#include <cstring>
#define MEMSET0(x) memset(x,0,sizeof(x))

using namespace std;

int N,n;
int theQue[5005];
int theNext[5005];

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

    cin>>N;
    for(int i=0;i<N;++i)
    {
        cin>>n;
        MEMSET0(theNext);
        MEMSET0(theQue);
        if(n<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x++;
            }
            cout<<endl;
        }
        else if(n-(n>>1)<=3)
        {
            int x = 1;
            while(x<=n)
            {
                cout<<x<<' ';
                x+=2;
            }
            cout<<endl;
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
            cout<<theQue[1]<<' ';
            if(theQue[theNext[1]])cout<<theQue[theNext[1]]<<' ';
            if(theQue[theNext[theNext[1]]])cout<<theQue[theNext[theNext[1]]];
            cout<<endl;
        }
    }

    return 0;
}
```
