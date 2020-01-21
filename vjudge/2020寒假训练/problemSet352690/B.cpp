/**
 *
 * 最小费用最大流 问题
 *
 * 所谓，就和包含长度和费用两个要素的问题一样
 * 只不过就是一个同样算法进行的优先级问题
 * 最大流是一定的，但不是唯一的，选择费用最少的最大流吧
 *
 * 从当前的可行流出发，寻找费用最少的增广流
 *
 * POJ的尿性：
 * abs(int):int 必须来自cstdlib
 * <<T> > 必须要有空格，不可以是>>
 * 不认识nullptr 无法读入优化
 *
 * TLE: 写的太丑了嘛…………
 */
#include <cstdio>
#include <utility>
#include <cstring>
#include <queue>
#include <cstdlib>

#define _suend_ (2+cnth+cntm)
#define X first
#define Y second

#define house(x) (1+x)
#define man(x) (1+cnth+x)

using namespace std;
struct edge { int togo,flow,capa,cost; };
typedef pair<int,int> point;

int n,m;
char map[105][105];
const int inf = 0x3f3f3f3f;

// front-star graph
edge edgelist[25010];
int head[250]{0};
int nextptr[25010];
int ptr = 0;

// build new graph
int cnth = 0;
int cntm = 0;
point hlist[105];
point mlist[105];
const int subegin = 1;
int suend;

// spfa & solution
int dis[250];
bool visit[250];
int pre[250];           // 用于记录路径：当前dis来源的边的指针
int maxflow,mincost;

inline void reInitialize()
{
    ptr = cnth = cntm = 0;
    memset(head,0,sizeof(head));
}

inline void addBiConnectEdge(int from,int to,int _capa,int _cost)
{
    ++ptr;
    nextptr[ptr] = head[from];
    head[from] = ptr;
    edgelist[ptr] = {to,0,_capa,_cost};
    ++ptr;
    nextptr[ptr] = head[to];
    head[to] = ptr;
    edgelist[ptr] = {from,0,0,-_cost};
}

inline int manhattan(const point& a,const point& b)
{
    return abs(a.X-b.X)+abs(a.Y-b.Y);
}

inline void buildGraph()
{
    suend = _suend_;
    for(int i=1;i<=cntm;++i)
    {
        addBiConnectEdge(subegin,man(i),1,0);
        for(int j=1;j<=cnth;++j)
            addBiConnectEdge(man(i),house(j),1,manhattan(mlist[i],hlist[j]));
        addBiConnectEdge(house(i),suend,1,0);
    }
}

inline bool spfa(int start,int end)
{
    queue<int> que;
    memset(visit, 0, sizeof(visit));
    memset(dis, 0x3f, sizeof(dis));
    memset(pre, 0, sizeof(pre));

    int thispoint;
    dis[start] = 0;
    visit[start] = true;
    que.push(start);

    while(!que.empty())
    {
        thispoint = que.front();
        que.pop();
        visit[thispoint] = false;
        int nowcost;

        for(int i=head[thispoint];i;i=nextptr[i])
        {
            edge& that = edgelist[i];
            nowcost = dis[thispoint]+that.cost;
            if( that.capa > that.flow &&                    // 剩余流条件
                dis[that.togo] > nowcost)                   // spfa 经典条件
            {
                dis[that.togo] = nowcost;
                pre[that.togo] = i;                         // 记录此边
                if(!visit[that.togo])
                {
                    visit[that.togo] = true;
                    que.push(that.togo);
                }
            }
        }
    }

    return pre[end];        // 空边为0；如果终点记录了路径，说明找到了，返回true
}

inline int solution()
{
    int ans = 0;

    mincost = maxflow = 0;
    while(spfa(subegin,suend))
    {
        int delta = inf;        // 尝试寻找增广流：最大剩余流量
        int differ;
        for(int i=pre[suend];i;i=pre[edgelist[i+1].togo])   // 按路径倒推
        {
            differ = edgelist[i].capa - edgelist[i].flow;
            if(delta > differ) delta = differ;
        }
        for(int i=pre[suend];i;i=pre[edgelist[i+1].togo])   // 刷新路径最大流
        {
            edgelist[i].flow += delta;
            edgelist[i+1].flow -= delta;
            mincost += delta*edgelist[i].cost;
        }
        maxflow += delta;
    }

    ans = mincost;
    reInitialize();
    return ans;
}

int main()
{
//    ios::sync_with_stdio(false);
//    cin.tie(nullptr);

    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        for(int i=1;i<=n;++i)
        {
            scanf("%s",map[i]+1);
            for(int j=1;j<=m;++j)
                if(map[i][j]=='m') mlist[++cntm] = {i,j};
                else if(map[i][j]=='H') hlist[++cnth] = {i,j};
        }
        buildGraph();
        printf("%d\n",solution());
    }

    return 0;
}