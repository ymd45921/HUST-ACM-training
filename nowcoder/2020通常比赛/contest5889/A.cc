/**
 *
 * 华为杯，中国地质大学 网络邀请赛
 */
#define USING_STDIO 1
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#endif

#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

template <int n> const int *EulerSieve()
{
    static int prime[n + 5];
    bool vis[n + 5] {false};
    int &cnt = prime[0] = 0;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; j <= cnt; ++ j)
        {
            if ((longs)i * prime[j] > n) break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    return prime;
}

const int N = 1e5;
int x[N], xx[N], sum[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    auto p = EulerSieve<500000>();
    auto cnt = p[0];
    auto fact = [&](int val) -> int
    {
        int lim = val, cur = 1;
        while ( p[cur] <= lim && val % p[cur])
            lim = val / p[cur ++];
        return val % p[cur] ? 1 : p[cur];
    };

    int t, n, a, b, c;
    t = nextInt();
    while (t --)
    {
        n = nextInt();
        a = nextInt(), b = nextInt(), c = nextInt();
        for (int i = 1; i <= n; ++ i)
        {
            x[i] = nextInt();
            xx[i] = fact(x[i]);
        }
    }

    return 0;
}