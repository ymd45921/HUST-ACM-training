/**
 * log的底数是e；log2的底数是2.
 *
 * double精度有问题。遇到就尽量转化为别的东西。
 * cost最后只是和关卡有关：你的级别越低花销越小。
 *
 * TLE: 原因是你弃用了cost但是还用它作为判据。
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

#define cost(a) ((double)a/(double)nowlvl+1)
#define nowpos cur.togo
#define nowlvl cur.lvl

#define _FORWARDSTAR_

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
    memset(edges,0,sizeof(edges));
    memset(headptr,0,sizeof(headptr));
    memset(nextptr,0,sizeof(nextptr));
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
        longs costs;
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
    if(lowlvl[0]==lowlvl[n])return false;
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
