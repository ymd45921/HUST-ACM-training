#include <cstdio>
#include <algorithm>
#define max(a,b) a>b?a:b
#define mylogx

using namespace std;
struct cow{int s;int e;};

int N,T,ans = 0;
cow cows[25050];

bool cmp(const cow& c1,const cow& c2)   // 保证每个s的第一项必然可以使队列延伸最长
{
    if(c1.s==c2.s)return c1.e>c2.e;
    else return c1.s<c2.s;
}

int main()
{
    scanf("%d%d",&N,&T);
    for(int i=0;i<N;++i)scanf("%d%d",&cows[i].s,&cows[i].e);
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
            ++cur;
        }
        if(maxtail>tail)                // 队列可以在连续的情况下延伸
        {
            tail = maxtail;
            ++ans;
            if(maxtail>=T)break;
        }
        else cur==N;                    // 队列无法保证连续，无解了。
    }
    if(cur==N&&tail<T)printf("-1");    //已经遍历所有可能依然没有全覆盖，告辞。
    else printf("%d",ans);
    return 0;
}