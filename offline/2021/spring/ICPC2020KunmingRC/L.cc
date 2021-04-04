#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read()
{
    ll x = 0; char ch = getchar();
    for(; ch > '9' || ch < '0'; ch = getchar());
    for(; ch >= '0' && ch <= '9'; ch = getchar())x = x * 10 + ch - 48;
    return x;
}
const int N = 1e6 + 2;
int a[N];
int stk[N];
bool vis[N];

int hd[N], nxt[N << 1], to[N << 1], tot;
inline void addedge(int u, int v)
{
    nxt[++tot] = hd[u]; hd[u] = tot; to[tot] = v;
    nxt[++tot] = hd[v]; hd[v] = tot; to[tot] = u;
}

void dfs(int u)
{
    if(vis[u]) return ;
    vis[u] = 1;
    for(int i = 1; )
}

int main()
{
    for(int T = read(); T--;) {
        int n = read();
        for(int i = 1; i <= n; ++i) a[i] = read();
        int ans = 0;
        int tp = -1;
        for(int i = 1; i <= n; ++i) {
           while(tp >= 0 && stk[tp] < a[i]) --tp;
           stk[++tp] = a[i];
           ans = max(ans, tp + 1);
        }
        for(int i = 1; i <= n; ++i) vis[i] = 0;
        for(int i = 1; i <= n; ++i)
            if(!vis[i]) dfs(i);
    }
    return 0;
}