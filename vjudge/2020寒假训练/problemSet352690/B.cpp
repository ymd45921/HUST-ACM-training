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

/*
 *
 * 爷麻了==
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdlib>

using namespace std;
struct edge
{
    int to;             // 边的远端点
    int flow;           // 边的当前剩余流量
    int cap;            // 边的最大容量
    int cost;           // 边单位流量费用
};
struct point { int x,y; };

// 实用函数、宏 的定义
inline int distance(const point& a,const point& b);

// 定义的常量
const int inf = 0x3f3f3f3f;
const int maxp = 500;
const int maxe = 25000;

// 链式前向星：建图
edge elist[maxe];
vector<point> houses,men;
int head[maxp];
int nextptr[maxe];
int ptr;

// SPFA最短路径需要使用的变量
int dis[maxp];          // 被初始化为INF，是起点到某点的最短距离
int path[maxp];         // 被初始化为-1，记录路径上到某点的的边的前向星编号
bool visit[maxp];       // 被初始化为0，记录某个特定点当前是否在队列中

void initialize()
{
    // 初始化：链式前向星
    memset(head,-1,sizeof(head));
    ptr = -1;
    houses.clear();
    men.clear();
}

/*
 * 加边：向链式前向星的图中增加新的网络流双向边
 *
 * @param from 边的起始点
 * @param to 边的终点
 * @param capacity 边的最大容量
 * @param cost 边的单位费用
 */
inline void add_edge(int from, int to, int capacity, int cost)
{
    ++ptr;                      // 正向边：必定为偶数
    nextptr[ptr] = head[from];
    head[from] = ptr;
    elist[ptr] = {to,capacity,capacity,cost};
    ++ptr;                      // 反向边：无容量，必定为奇数
    nextptr[ptr] = head[to];
    head[to] = ptr;
    elist[ptr] = {from,0,0,-cost};
}

bool spfa(int s,int t)
{
    queue<int> que;
    memset(dis,0x3f,sizeof(dis));
    memset(path,-1,sizeof(path));
    memset(visit,0, sizeof(visit));

    dis[s] = 0;
    visit[s] = true;
    que.push(s);
    int thispoint,that,nowdis;

    while(!que.empty())
    {
        thispoint = que.front();
        que.pop();
        visit[thispoint] = false;

        for(int i=head[thispoint];~i;i=nextptr[i])
        {
            that = elist[i].to;
            nowdis = dis[thispoint]+elist[i].cost;
            if(elist[i].flow>0 && dis[that]>nowdis)
            {
                dis[that] = nowdis;
                path[that] = i;
                if(!visit[that])
                {
                    visit[that] = true;
                    que.push(that);
                }
            }
        }
    }

    return ~path[t];
}

int solution(int s,int t)
{
    int min_cost = 0;
    int max_flow = 0;
    while(spfa(s,t))
    {
        int delta = inf;
        for(int i=path[t];~i;i=path[elist[i|1].to])
            delta = min(delta,elist[i].flow);
        for(int i=path[t];~i;i=path[elist[i|1].to])
        {
            elist[i].flow -= delta;
            elist[i|1].flow += delta;
            min_cost += elist[i].cost*delta;
        }
        max_flow += delta;
    }
    return min_cost;
}

int main()
{
    int n,m;
    char s[105];

    while(~scanf("%d%d",&n,&m))
    {
        if(!n && !m) return 0;
        initialize();

        for(int i=1;i<=n;++i)
        {
            scanf("%s",s+1);
            for(int j=1;j<=m;++j)
                if(s[j]=='H')houses.push_back({i,j});
                else if(s[j]=='m')men.push_back({i,j});
        }
        const int houses_size = houses.size();
        const int men_size = men.size();

        const int begin = 0;
        const int end = houses_size+men_size+1;
        for(int i=0;i<men_size;++i)
        {
            add_edge(begin,i+1,1,0);
            for(int j=0;j<houses_size;++j)
                add_edge(i+1,j+1+men_size,1,distance(men[i],houses[j]));
            add_edge(i+1+men_size,end,1,0);
        }

        int ans = solution(begin,end);
        printf("%d\n",ans);
    }

    return 0;
}

// 实用函数、宏 的实现
inline int distance(const point& a,const point& b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}

/* 有一个TLE的版本 */
/*
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>

#define man(x) (x)
#define house(x) (x+cntm)
#define distance(m,h) (abs(houselist[h].x-manlist[m].x)+abs(houselist[h].y-manlist[m].y))
#define superend() (cnth+cntm+1)

#define now (edgelist[i])
#define nowrev (edgelist[i|1])
#define pre(x) (edgelist[i|1].to)

using namespace std;
struct edge {int to,surf,cap,cost;};    // 边的终点，剩余流量，容量，单位费用
struct point {int x,y;};

// constant quantities
const int inf = 0x3f3f3f3f;
const int maxn = 105;
const int maxpt = 250;
const int maxnum = 20500;
const int superbegin = 0;

//constant variables
int superend;
int cntm,cnth;

// standard I/O
int n,m;
char map[maxn][maxn];
point houselist[maxn];
point manlist[maxn];

// forward-star graph (-1)
int head[maxpt];
int nextptr[maxnum];
edge edgelist[maxnum];
int ptr = -1;

// spfa field
int visit[maxpt];
int path[maxpt];
int dis[maxpt];

// MCMF solution field
int maxFlow = 0;
int minCost = 0;

// flow functions
inline void initialize();
inline void buildgraph();
inline void solution();
void addbiedge(int from,int to,int capacity,int cost);
bool spfa(int s,int t);

int main()
{
    while(scanf("%d%d",&n,&m)&&n&&m)
    {
        initialize();
        for(int i=1;i<=n;++i)
        {
            scanf("%s",map[i]+1);
            for(int j=1;j<=m;++j)
                if(map[i][j] == 'H')
                    houselist[++cnth] = {i,j};
                else if(map[i][j] == 'm')
                    manlist[++cntm] = {i,j};
        }

        buildgraph();
        solution();
        printf("%d\n",minCost);
    }
    return 0;
}

inline void initialize()
{
    memset(head,-1, sizeof(head));
    ptr = -1;
    cntm = cnth = 0;
    minCost = maxFlow = 0;
}

inline void buildgraph()
{
    superend = superend();
    for(int i=1;i<=cntm;++i)
    {
        addbiedge(superbegin,man(i),1,0);
        for(int j=1;j<=cnth;++j)
            addbiedge(man(i),house(j),1,distance(i,j));
        addbiedge(house(i),superend,1,0);
    }
}

void addbiedge(int from,int to,int capacity,int cost)
{
    ++ptr;
    nextptr[ptr] = head[from];
    head[from] = ptr;
    edgelist[ptr] = {to,capacity,capacity,cost};
    ++ptr;
    nextptr[ptr] = head[to];
    head[to] = ptr;
    edgelist[ptr] = {from,0,0,-cost};
}

bool spfa(int s,int t)
{
    memset(dis,0x3f,sizeof(dis));
    memset(path,-1,sizeof(path));
    memset(visit,0, sizeof(visit));
    queue<int> que;

    que.push(s);
    dis[s] = 0;
    int thispoint,that;
    while(!que.empty())
    {
        thispoint = que.front();
        que.pop();
        visit[thispoint] = false;

        for(int i=head[thispoint];~i;i=nextptr[i])
        {
            that = now.to;
            int nowdis = dis[thispoint]+now.cost;
            if(now.surf > 0 && dis[that] > nowdis)
            {
                dis[that] = nowdis;
                path[that] = i;
                if(!visit[that])
                {
                    que.push(that);
                    visit[that] = true;
                }
            }
        }
    }

    return ~path[t];
}

inline void solution()
{
    while(spfa(superbegin,superend))
    {
        int delta = inf;
        for(int i=path[superend];~i;i=path[pre(i)])
            if(delta>now.surf) delta = now.surf;
        for(int i=path[superend];~i;i=path[pre(i)])
        {
            now.surf -= delta;
            nowrev.surf += delta;
        }
        maxFlow += delta;
        minCost += delta*dis[superend];
    }
}
*/

/* 一个TLE了的版本 */
/*
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
*/
