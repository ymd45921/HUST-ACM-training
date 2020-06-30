/**
 *
 * 带权 LCA
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 2e5 + 5, M = N;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M*2];

    void init(int n = N-1)
    {
        memset(head, -1, sizeof(int)*(n+1));
        tot = 0;
    }

    void addEdge(int u, int v, int w)
    {
        ee[tot] = edge(u,v,w,head[u]);
        head[u] = tot ++;
        ee[tot] = edge(v,u,w,head[v]);
        head[v] = tot ++;
    }

}

char h[N];

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int n, q, c, w, m;
    cin >> n >> q >> c >> w >> (h + 1);
    auto weigh = [&](int u, int v)
    {
        if (h[u] == h[v])
            if (h[u] == '0') return c + w;
            else return c + w + w;
        else return c + c + w + w;
    };
    auto appendix = [&](int a, int b)
    {
        return c + w + w +
                (h[a] == '1' ? w : 0) +
                (h[b] == '1' ? w : 0);
    };
    m = n - 1; FWS::init(n + 1);
    while (m --)
    {
        int u, v;
        cin >> u >> v;
        FWS::addEdge(u, v, weigh(u, v));
    }
    while (q --)
    {
        int a, b;
        cin >> a >> b;


    }



    return 0;
}