#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

#define mylog
#define MAXLEN 1050

using namespace std;

int n,m,k,x,y;
vector<int> edge[MAXLEN];   //特定节点持有的边的另一端点
int father[MAXLEN]{0};      //特定节点所属的连通块，0：未所属
int member[MAXLEN]{0};      //连通块的规模
bool police[MAXLEN]{0};     //连通块flag中是否包括警察
vector<int> blockWithPolice;
int nodeWithoutPolice = 0;

//函数：依据规模比较通过序号访问的并查集
inline bool UFcmp(int x, int y)
{
    return member[x]>member[y];
}

inline int calculate(int n)
{
    return (n*n-n)>>1;
}

//函数：BFS包含o的连通块，并且将它们标记为属于flag
//此时，标记flag象征了一个并查集（连通块）
//搜索的起点o必须是孤儿或者属于编号为o的并查集
void bfs(int o, int flag)
{
    queue<int> que;
    que.push(o);
    int top;

    while(!que.empty())
    {
        top = que.front();
        father[top] = flag;
        ++member[flag];
        police[flag] |= police[top]; 
        for(int i : edge[top])
        {
            if(!father[i])  //如果是孤儿，就加入待搜索队列
            que.push(i);
            father[i] = flag;
        }
        que.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int maxEdge = 0;
    int ans;

    cin>>n>>m>>k;
    for(int i=0;i<k;++i)
    {
        cin>>x;
        police[x] = true;
    }
    for(int i=0;i<m;++i)
    {
        cin>>x>>y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }

    for(int i=1;i<=n;++i)
    {
        if(father[i])continue;
        bfs(i,i);
        if(police[i])
            blockWithPolice.push_back(i);
        else
            nodeWithoutPolice+=member[i];
    }

    sort(blockWithPolice.begin(),
         blockWithPolice.end(),
         UFcmp);
    maxEdge+=calculate(member[blockWithPolice[0]]+
                       nodeWithoutPolice);
    for(int i=1;i<blockWithPolice.size();++i)
    {
        maxEdge+=calculate(member[blockWithPolice[i]]);
    }
    ans = maxEdge - m;
    cout<<ans;
    return 0;
}