/**
 * 虽然是一道紫色的题目，但是题解的带佬们说模拟就能过：
 * 
 * 在意Tag中提到的并查集————
 * 主要是应用在判断无向图中环的数量上：
 * - 每次输入一条边
 * - 如果两个顶点不在同一集合中，就把他俩合为一个集合中
 * - 已经在一个集合中了，说明只要加上这条边，就会形成一个环
 * - 处理完所有的边之后，剩余的集合数量就是联通图个数
 * 并查集方法可以同时判断连通性和回路。
 * 这里参考了一个很朴素的并查集的写法，多学习学习！
 * 
 * 如果不使用并查集的方法，这两个判定都需要进行DFS/BFS遍历
 * 连通图：DFS或BFS搜索并且判断最终的count值
 * 
 * 不是说好了暴力模拟也能过嘛？怎么给我炸了个TLE呢？有问题
 */
#include <iostream>
#include <string>
#include <queue>
#include <cstring>

#define out(i) map[i][0]
#define in(i) map[0][i]

using namespace std;

int n,m;
int tmpx,tmpy;
int set[105];           //并查集建图
int rx,ry;
bool visited[105]{0};

const string output[] = {"NO","FHTAGN!"};

//利用当前的并查集模型寻找属于的并查集
inline int father(int node)
{
    int cur = node;
    while(set[cur]-cur)
    {
        cur = set[cur];
    }
    return cur;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    
    //图论知识：连通图存在环路必然有m>=n
    if(m<n)
    {
        cout<<output[false];
        return 0;
    }

    //初始化并查集：set[i]=i 代表以i为根节点的独立集合
    for(int i=0;i<=n;++i)
        set[i] = i;

    int iter = m;
    int loop = 0;
    while(iter--) 
    {
        cin>>tmpx>>tmpy;
        set[tmpx] = rx = father(tmpx);
        set[tmpy] = ry = father(tmpy);
        if(rx==ry)++loop;
        set[rx] = ry;
    }

    //利用并查集检查连通分量的数量
    int cnt = 0;
    for(int i=1;i<=n;++i)
    {
        if(set[i]==i)
        {
            ++cnt;
            if(cnt>1)
            break;
        }
    }

    if(loop==1 && cnt==1)
        cout<<output[true];
    else cout<<output[false];
    return 0;
}