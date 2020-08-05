/**
 *
 * 一定是二叉树，并且要求左子树右子树的高度差不能超过 1
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

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

const int N = 5e5 + 5, INF = 0x3f3f3f3f, M = N;
bool erased[N];
int size[N];

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

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
    }

    void getSize(int u)
    {
        size[u] = 1;
        for (int c = head[u]; ~c; c = ee[c].next)
        {
            int v = ee[c].v;
            getSize(v);
            size[u] += size[v];
        }
    }
}

int res = 0;
void deleteDFS(int u, bool find = true)
{
    using namespace FWS;
    if (!find)
    {
        erased[u] = true;
        for (int c = head[u]; ~c; c = ee[c].next)
            deleteDFS(ee[c].v, false);
    }
    else if (size[u] > res)
    {
        vector<int> li;
        for (int c = head[u]; ~c; c = ee[c].next)
            li.push_back(ee[c].v);
        sort(li.begin(), li.end());
        for (auto ii = li.rbegin(); ii != li.rend(); ++ ii)
            deleteDFS(*ii);
    }
    else
    {
        res -= size[u];
        erased[u] = true;
        for (int c = head[u]; ~c; c = ee[c].next)
            deleteDFS(ee[c].v, false);
    }
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif
    int n, k, p, root;
    cin >> n >> k;
    res = n - k; FWS::init(n);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> p;
        if (p == -1) root = i;
        else FWS::addEdge(p, i, 0);
    }
    FWS::getSize(root);
    deleteDFS(root);

    for (int i = 1; i <= n; ++ i) cout << !erased[i];
    cout << endl;

    return 0;
}