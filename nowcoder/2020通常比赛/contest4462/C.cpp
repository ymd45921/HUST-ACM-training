/**
 * 
 * 预处理所有的情况随便DFS可也太顶了==
 * 不过u1s1这个题目的范围也不大，确实怎么做都可以
 * 
 * 
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

int ans[1<<13];
char ch;

int dfs(int p)
{
    if(~ans[p])return ans[p];
    int cnt = 0;
    for(int i=1,msk=1;i<=12;++i,msk<<=1)
        if(msk&p)++cnt;
    ans[p] = cnt;
    int m1=1,m2=2,m3=4;
    for(int i=1;i<=10;++i,m1<<=1,m2<<=1,m3<<=1)
    {
        if(!(m1&p)&&(m2&p)&&(m3&p))
            ans[p] = min(ans[p],dfs(p+m1-m2-m3));
        else if((m1&p)&&(m2&p)&&!(m3&p))
            ans[p] = min(ans[p],dfs(p-m1-m2+m3));
    }
    return ans[p];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    memset(ans,-1,sizeof(ans));
    while(cin>>n)
    {
        while(n--)
        {
            int in = 0;
            for(int i=0;i<12;++i)
            {
                cin>>ch;
                in<<=1;
                if(ch=='o') in|=1;
            }
            cout<<dfs(in)<<endl;
        }
    }

    return 0;
}