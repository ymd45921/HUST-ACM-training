/**
 * log的底数是e；log2的底数是2.
 *
 * double精度有问题。遇到就尽量转化为别的东西。
 * cost最后只是和关卡有关：你的级别越低花销越小。
 * 
 * TLE: 
 */
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

#define cost(a) ((double)(nowlvl+a)/(double)nowlvl)
#define nowpos cur.togo
#define nowlvl cur.lvl

using namespace std;
typedef long long longs;
typedef long double longd;
struct edge
{
    int togo;
    longs lvl;
    longs lcost;     
    bool operator<(const edge& rhs) const;
    bool operator>(const edge& rhs) const;
};
typedef priority_queue<edge,vector<edge>,greater<edge>> heap;

int t,n,m;
int u,v,a,b;
longd ans = 0;
vector<edge> edgelist[100010];
longs lowlvl[100010];

inline void all_clear()
{
    for(int i=1;i<=n;++i)edgelist[i].clear();
    ans = 0;
}

inline void add_edge(int u,int v,int a,int b)
{
    edgelist[u].push_back({v,a,1<<b});
}

inline bool dijkstra()
{
    heap table;
    memset(lowlvl,0x3f,sizeof(lowlvl));

    lowlvl[1] = 1;    // log2(1) = 0
    table.push({1,1,1});
    edge cur;
    while(!table.empty())
    {
        cur = table.top();
        table.pop();
        if(lowlvl[nowpos]<=nowlvl)continue;
        longs costs;

        for(auto i : edgelist[nowpos])
        {
            costs = cost(i.lvl);
            if(costs<i.lcost)continue;
            if(lowlvl[i.togo]>nowlvl+i.lvl)
            {
                lowlvl[i.togo] = nowlvl+i.lvl;
                table.push({i.togo,lowlvl[i.togo],1});
            }
        }
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

bool edge::operator<(const edge& rhs) const
{
    return lcost<rhs.lcost;
}

bool edge::operator>(const edge& rhs) const
{
    return lcost>rhs.lcost;
}
