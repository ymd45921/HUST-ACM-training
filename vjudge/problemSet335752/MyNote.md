# HUST-ACM 2019基本算法专项练习

专题：贪心 日期：2019-10-17

## Problem A

**Version 1** : 编译器找不到`nullptr`标识，编译失败。然后还WA了。
```c++
#include <iostream>
#include <algorithm>
#define max(a,b) a>b?a:b

using namespace std;
struct cow{int s;int e;};

int N,T,ans = 0;
cow cows[25050];

bool cmp(const cow& c1,const cow& c2)
{
    if(c1.s==c2.s)return c1.e>c2.e;
    else return c1.s<c2.s;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N>>T;
    for(int i=0;i<N;++i)cin>>cows[i].s>>cows[i].e;
    sort(cows,cows+N,cmp);
    int cur = 0;
    int tail = 0,maxtail,lim;
    for(cur=0;cur<N;++cur)
    {
        lim = tail+1;
        maxtail = tail;
        while(cows[cur].s<=lim)
        {
            maxtail = max(maxtail,cows[cur].e);
            ++cur;
        }
        if(maxtail>tail)
        {
            tail = cows[cur].e;
            ++ans;
        }
        else cur==N;
    }
    if(cur==N&&tail!=T)cout<<-1;
    else cout<<ans;
    return 0;
}
```
解决方案：使用纯C.重写。  
WA问题所在：一堆毛病==提交前请先测试

**Version 2** : TLE.
解决方案：跳过同样的s值。搞个树存一下索引？用数组存一下步长还是会TLE。
```c++
#include <cstdio>
#include <algorithm>
#include <cstring>
#define max(a,b) a>b?a:b
#define mylogx

using namespace std;
struct cow{int s;int e;};

int N,T,ans = 0;
cow cows[25050];
int step[1000050];

bool cmp(const cow& c1,const cow& c2)   // 保证每个s的第一项必然可以使队列延伸最长
{
    if(c1.s==c2.s)return c1.e>c2.e;
    else return c1.s<c2.s;
}

int main()
{
    scanf("%d%d",&N,&T);
    memset(step,0,sizeof(step));
    for(int i=0;i<N;++i)
    {
        scanf("%d%d",&cows[i].s,&cows[i].e);
        ++step[cows[i].s];
    }
    sort(cows,cows+N,cmp);
    cows[N] = {25050,50100};
#ifdef mylog
    for(int i=0;i<N;++i)printf("<%d,%d> ",cows[i].s,cows[i].e);
    printf("\n");
#endif
    int cur = 0;                        // 当前光标从0开始向后查找
    int tail = 0,maxtail,lim;           // 初始队列的队尾在0（无覆盖）
    for(cur=0;cur<N;)
    {
        lim = tail+1;                   // 保证新加入队列可以连续
        maxtail = tail;                 // 本轮循环中找到的连续最长队尾延伸
        while(cows[cur].s<=lim)
        {
            maxtail = max(maxtail,cows[cur].e);
            cur+=step[cows[cur].s];
        }
        if(maxtail>tail)                // 队列可以在连续的情况下延伸
        {
            tail = maxtail;
            ++ans;
            if(maxtail>=T)break;
        }
        else cur==N;                    // 队列无法保证连续，无解了。
    }
    if(cur==N&&tail<T) printf("-1");    //已经遍历所有可能依然没有全覆盖，告辞。
    else printf("%d",ans);
    return 0;
}
```