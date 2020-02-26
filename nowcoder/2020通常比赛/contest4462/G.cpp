/**
 * 
 * 这个题目怎么有种既视感==
 * 
 * C++4s，暴搜能过，好
 * 
 * 但是还是又能做的事情的，比如优化，比如还有一个老哥
 * 提出了一个看起来还有点意思的中位数方法。
 */
#include <iostream>
#include <cstring>
#include <utility>

using namespace std;
typedef long long longs;
typedef long double longd;

int mat[105][105];
longs row[105],col[105];    // 行、列的总值
longs res = 0;

pair<int,int> midium(int n,int m)
{
    const longs half = res+1>>1;
    longs tmp; int i,j;
    for(i=1,tmp=0;i<=m,tmp<half;++i)
        tmp += row[i];
    for(j=0,tmp=0;j<=n,tmp<half;++j)
        tmp += col[j];
    return make_pair(--i,--j);  // for检查会多+1
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T,n,m;
    while(cin>>T)while(T--)
    {
        cin>>n>>m;
        res = 0;
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j)
            {
                cin>>mat[i][j];
                row[i]+=mat[i][j];
                col[j]+=mat[i][j];
                res+=mat[i][j];
            }
        auto mid = midium(n,m);
        int &x = mid.first, &y = mid.second;
        longs out = 0;
        for(int i=1;i<=m;++i)
            for(int j=1;j<=n;++j)
                out += mat[i][j]*(abs(i-x)+abs(j-y));
        cout<<out<<endl;
    }

    return 0;
}