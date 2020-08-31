#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned long long ulongs;

const int N = 100010;
const ulongs mod = 1e9 + 7;

int m,n,f[N];
ulongs k1,k2;
struct edge
{
    int u,v;
    ulongs w;

    bool operator<(const edge& b) const
    {
        if (w != b.w) return w < b.w;
        if (u != b.u) return u < b.u;
        return v < b.v;
    }
} e[N];

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

ulongs xorShift128Plus()
{
    ulongs k3=k1,k4=k2;
    k1=k4;
    k3^=k3<<23;
    k2=k3^k4^(k3>>17)^(k4>>26);
    return k2+k4;
}

void gen()
{
    scanf("%d%d%llu%llu",&n,&m,&k1,&k2);
    for (int i=1; i<=n; i++)
        f[i] = i;
    for (int i=1; i<=m; i++)
    {
        e[i].u = xorShift128Plus() % n+1;
        e[i].v = xorShift128Plus() % n+1;
        e[i].w = xorShift128Plus();
        if (e[i].u > e[i].v) swap(e[i].u,e[i].v);
    }
}

void kurskal()
{
    gen();
    sort(e+1,e+1+m);
    int cnt=0;
    ulongs cost=0,time=1,res;
    for (int i=1; i<=m; i++)
    {
        int fu=find(e[i].u),fv=find(e[i].v);
        if (fu!=fv)
        {
            res=1;
            f[fu]=fv;
            cost=(cost+e[i].w)%mod;
            cnt++;
            while (i+1<=m && e[i].u==e[i+1].u &&
                e[i].v==e[i+1].v && e[i].w==e[i+1].w
            )
            {
                i++;
                res++;
            }
            time=time*res%mod;
        }
        if (cnt==n-1) break;
    }
    if (cnt==n-1) printf("%llu\n",cost%mod*time%mod);
    else printf("0\n");
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--) kurskal();
    return 0;
}