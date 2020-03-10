/**
 *
 * 这是一个最小Steiner Tree的问题
 *
 * 给了两种解题方法
 *
 *
 * 先不管什么Steiner Tree，这个是不是bfs就好了？
 *
 * 正确性：如果在一条路上怎么回头路？一定存在按照顺序的演进方法更新这种情况
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

#define norm 0
#define iron 1
#define coal 2

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

struct edge
{
    int to,next;
};

const int N = 2e5+5;
const int INF = 0x1f1f1f1f;     // 因为会出现3*INF，所以不能是0x3f3f3f3f
const char cannot[] = "impossible";

int n,m,k;
int o[N],c[N];
int a,b;
int dis[3][N];  // dis[!norm]代表了从某点能到达的最近的矿源的距离

int head[N];
edge e[(N<<1)+(N<<3)];
int tot = -1;
int tail[N];
edge re[(N<<1)+(N<<3)];

inline void init()
{
    tot = -1;
    memset(head,-1,sizeof(int)*(n+1));
    memset(tail,-1,sizeof(int)*(n+1));
    memset(dis[0],0x1f,sizeof(int)*(n+1));
    memset(dis[1],0x1f,sizeof(int)*(n+1));
    memset(dis[2],0x1f,sizeof(int)*(n+1));
}

inline void addedge(int u, int v)
{
    ++tot;
    e[tot] = {v,head[u]};
    head[u] = tot;
    re[tot] = {u,tail[v]};
    tail[v] = tot;
}

void BFS(int typ)
{
    queue<int> q;
    if(typ)
    {
        if(typ==iron)
            for(int i=1;i<=m;++i)
                q.push(o[i]), dis[iron][o[i]] = 0;
        else for(int i=1;i<=k;++i)
                q.push(c[i]), dis[coal][c[i]] = 0;
        while(!q.empty())
        {
            int top = q.front();
            q.pop();
            int c = tail[top];
            while(~c)
            {
                if(dis[typ][re[c].to] > dis[typ][top]+1)
                {
                    dis[typ][re[c].to] = dis[typ][top]+1;
                    q.push(re[c].to);       // 有可能更新距离时再更新
                }
                c = re[c].next;
            }
        }
    }
    else
    {
        q.push(1);
        dis[norm][1] = 0;
        while(!q.empty())
        {
            int top = q.front();
            q.pop();
            int c = head[top];
            while(~c)
            {
                if(dis[norm][e[c].to] > dis[norm][top]+1)
                {
                    dis[norm][e[c].to] = dis[norm][top]+1;
                    q.push(e[c].to);
                }
                c = e[c].next;
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

//    freopen(R"(D:\shiroha\Downloads\nwerc2016testdata.tar\nwerc2016testdata\iron_and_coal\022_one_ore_of_many.in)","r",stdin);

    cin>>n>>m>>k;
    init();
    dis[norm][1] = 0;
    for(int i=1;i<=m;++i)
        cin>>o[i];
    for(int i=1;i<=k;++i)
        cin>>c[i];
    for(int i=1;i<=n;++i)
    {
        cin>>a;
        while(a--)
            cin>>b, addedge(i,b);
    }

    BFS(norm);
    BFS(iron);
    BFS(coal);

    int ans = INF;
    for(int i=1;i<=n;++i)
        ans = min(ans,dis[norm][i]+dis[iron][i]+dis[coal][i]);
    if(ans-INF) cout<<ans<<endl;
    else cout<<cannot<<endl;

    return 0;
}