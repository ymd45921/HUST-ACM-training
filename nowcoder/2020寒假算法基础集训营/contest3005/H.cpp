/**
 * 
 * 这题目怎么觉得读着逼仄呢
 * 
 * 想要前缀和维护不同颜色的车的数量，但是这太大了
 * 
 * 题解说要使用树状数组，我也知道树状数组
 * 可是我为什么就不知道该怎么做呢==
 * 
 * 且不说树状数组。统计一次之后爽完了再加到另一侧不好吗？
 * 
 * 这个 p-=p&-p 到底啥意思啊？
 * 欸？你知道的树状数组不是真正的树状数组？
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

struct car
{
    int col,l,r;
};

const int N = 500005;

int n;
car train[N];
int rsum[N],lsum[N];
int ans[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(lsum,0,sizeof(int)*(n+1));
        memset(rsum,0,sizeof(int)*(n+1));
        for(int i=1;i<=n;++i)
        {
            cin>>train[i].col>>train[i].l>>train[i].r;
            ++rsum[train[i].col];
        }
        for(int i=1;i<=n;++i)
        {

        }
    }

    return 0;
}