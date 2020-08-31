/**
 * log的底数是e；log2的底数是2.
 *
 * double精度有问题。遇到就尽量转化为别的东西。
 * cost最后只是和关卡有关：你的级别越低花销越小。
 *
 * TLE: 原因是弃用了lcost但是还用它作为判据。
 * WA: 重写的版本最后一个错误是比较的时候没有log2，推测原版本也是这方面混乱了
 */
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <cstring>
#include <utility>

#define lvl first
#define num second

using namespace std;
typedef long long longs;
typedef pair<longs,int> point;
struct edge {int to; longs a,b;};
typedef priority_queue<point,vector<point>,greater<point> > heap;

// information IO
int t,n,m;
int u,v;
longs a,b;

// forward-star
int head[100010];
edge elist[200020];
int nextptr[200010];
int ptr;

// dijkstra
longs dis[100010];
bool vis[100010];

inline void initialize()
{
    memset(head,0,sizeof(head));
    ptr = 0;
}

inline void addedge(int u,int v,longs a,longs b)
{
    ++ptr;
    nextptr[ptr] = head[u];
    head[u] = ptr;
    elist[ptr] = {v,a,b};
}

inline longs dijkstra()
{
    heap que;
    memset(dis,0x3f,sizeof(dis));
    memset(vis,0,sizeof(vis));
    const longs inf = dis[0];

    dis[1] = 1;
    que.push({1,1});
    point cur;
    long double cost;

    while(!que.empty())
    {
        cur = que.top();
        que.pop();
        if(vis[cur.num])continue;
        vis[cur.num] = true;

        for(int i=head[cur.num];i;i=nextptr[i])
        {
            edge& now = elist[i];
            cost = (long double)(cur.lvl+now.a)/cur.lvl*1.0;
            if(log2l(cost)<elist[i].b) continue;
            if(dis[now.to]>dis[cur.num]+now.a)
            {
                dis[now.to] = dis[cur.num]+now.a;
                que.push({dis[now.to],now.to});
            }
        }
    }

    if(dis[n]==inf)return -1;
    else return log2l(dis[n]);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    while(t--)
    {
        initialize();
        cin>>n>>m;
        while(m--)
        {
            cin>>u>>v>>a>>b;
            addedge(u,v,a,b);
        }
        cout<<dijkstra()<<endl;
    }

    return 0;
}


/*
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

#define cost(a) ((double)a/(double)nowlvl+1.0)
#define nowpos cur.togo
#define nowlvl cur.lvl

#define _EDGELIST_

using namespace std;
typedef long long longs;
typedef long double longd;
struct edge
{
#ifdef _FORWARDSTAR_
    int from;
#endif
    int togo;
    longs lvl;
    longs lcost;
};
struct point
{
    int togo;
    longs lvl;
    bool operator<(const point& rhs) const;
    bool operator>(const point& rhs) const;
};
typedef priority_queue<point,vector<point>,greater<point>> heap;

int t,n,m;
int u,v,a,b;
longd ans = 0;
longs lowlvl[100010];
#ifdef _EDGELIST_
vector<edge> edgelist[100010];
#elif defined _FORWARDSTAR_
edge edges[200010];
int ptr = 0;
int headptr[100010]{0};
int nextptr[200010]{0};
int cnt[100010]{0};
#endif

inline void all_clear()
{
#ifdef _EDGELIST_
    for(int i=1;i<=n;++i)edgelist[i].clear();
#elif defined _FORWARDSTAR_
    memset(headptr,0,sizeof(headptr));
    memset(cnt,0,sizeof(cnt));
    ptr = 0;
#endif
    ans = 0;
}

inline void add_edge(int u,int v,int a,int b)
{
#ifdef _EDGELIST_
    edgelist[u].push_back({v,a,1<<b});
#elif defined _FORWARDSTAR_
    ++ptr;
    nextptr[ptr] = headptr[u];
    headptr[u] = ptr;
    edges[ptr] = {u,v,a,1<<b};
    ++cnt[u];
#endif
}

inline bool dijkstra()
{
    heap table;
    memset(lowlvl,0x3f,sizeof(lowlvl));

    lowlvl[1] = 1;    // log2(1) = 0
    table.push({1,1});
    point cur;
    while(!table.empty())
    {
        cur = table.top();
        table.pop();
        if(lowlvl[nowpos]<nowlvl)continue;
        longd costs;
#ifdef _EDGELIST_
        for(auto i : edgelist[nowpos])
        {
            costs = cost(i.lvl);
            if(costs<i.lcost)continue;
            if(lowlvl[i.togo]>nowlvl+i.lvl)
            {
                lowlvl[i.togo] = nowlvl+i.lvl;
                table.push({i.togo,lowlvl[i.togo]});
            }
        }
#elif defined _FORWARDSTAR_
        for(int i=headptr[nowpos];i;i=nextptr[i])
        {
            costs = cost(edges[i].lvl);
            if(costs<edges[i].lcost) continue;
            if(lowlvl[edges[i].togo]>nowlvl+edges[i].lvl)
            {
                lowlvl[edges[i].togo] = nowlvl+edges[i].lvl;
                table.push({edges[i].togo,lowlvl[edges[i].togo]});
            }
        }
#endif
    }
    if(0x3f3f3f3f3f3f3f3f==lowlvl[n])return false;
    else
    {
        ans = log2l(lowlvl[n]);
        return true;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    for(int i=1;i<=t;++i)
    {
        cin>>n>>m;
        for(int i=0;i<m;++i)
        {
            cin>>u>>v>>a>>b;
            add_edge(u,v,a,b);
        }
        if(!dijkstra())cout<<-1<<endl;
        else cout<<floor(ans)<<endl;
        all_clear();
    }

    return 0;
}

bool point::operator<(const point& rhs) const
{
    return lvl<rhs.lvl;
}

bool point::operator>(const point& rhs) const
{
    return lvl>rhs.lvl;
}
*/
