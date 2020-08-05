#include <cstdio>
#include <cstring>
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

using namespace std;

int N,T,ans = 0;
int tindex,tend;
int step[1000050];

int main()
{
    scanf("%d%d",&N,&T);
    memset(step,0,sizeof(step));
    for(int i=0;i<N;++i)
    {
        scanf("%d%d",&tindex,&tend);
        step[tindex]=max(step[tindex],tend);
    }

    int cur = 0, last = 0;
    int tail = 0;
    while(cur<=T)
    {
        last = tail;
        int lim = tail+1;
        for(;cur<=lim;++cur)tail = max(tail,step[cur]);
        // tail = min(tail,T);
        if(tail==last)
        {
            break;
        }
        else
        {
            ++ans;
            if(tail==T)break;
        }
    }
    if(tail<T)ans = -1;
    printf("%d",ans);
    return 0;
}