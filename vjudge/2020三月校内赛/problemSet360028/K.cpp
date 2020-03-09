/**
 * 
 * 树你的🐎呢，这是一个容斥原理的水题
 * 我没看出来，我操，我死了
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

struct edge
{
    int next,to;
};

const int MOD = 1e9 + 7;
const int N = 2550;

// int head[N]{0};
// int tot;
// edge e[N];
// int chcnt[N]{0},dep[N];

int p[N],c[N][N];

// inline void init(int n)
// {
//     memset(p,0,sizeof(int)*(n+1));
//     memset(cnt,0,sizeof(int)*(n+1));
//     memset(head,-1,sizeof(int)*(n+1));
//     memset(chcnt,0,sizeof(int)*(n+1));
//     tot = -1;
// }

// inline void addedge(int u, int v)
// {
//     ++tot;
//     e[tot].next = head[u];
//     head[u] = tot;
//     e[tot].to = v;
//     ++chcnt[u];
// }

// void dfs(int i,int depth)
// {
//     dep[i] = depth;
//     ++cnt[depth];
//     int c = head[i];
//     const int nextdep = depth+1;
//     while(~c)
//     {
//         dfs(e[c].to,nextdep);
//         c = e[c].next;
//     }
// }

longs fastpow(longs a,int n)
{
    longs ans = 1;
    while(n>0)
    {
        if(n&1) ans = ans%MOD*a;
        a = a*a%MOD;
        n >>= 1;
    }
    return ans %= MOD;
}

longs minusMod(longs a, longs b)
{
    a += MOD;
    return (a-b)%MOD;
}

inline void initialCalculate()
{
    for(int i=0;i<N;++i) 
    {
        c[i][0] = 1;
        c[i][1] = i;
    }
    for(int i=0;i<N;++i) 
        for(int j=2;j<=i;++j)
            c[i][j] = (c[i-1][j]+c[i-1][j-1])%MOD;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,k;
    initialCalculate();
    while(cin>>n>>k)
    {
        // init(n);
        for(int i=1;i<n;++i)
        {
            cin>>p[i];
            // addedge(p[i],i);
        }

        const int children = n-1;
        longs sum = 0;
        int flag = 1;
        for(int i = k; i >= 1; --i)
        {
            longs tmp = flag*i*fastpow(i-1,children)%MOD*c[k][i];
            sum = (sum + tmp + MOD) % MOD;
            flag = -flag; 
        }

        cout<<sum<<endl;  
    }

    return 0;
}