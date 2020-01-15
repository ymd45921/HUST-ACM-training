/**
 * 二分图最大匹配
 * König定理：最小覆盖点数=最大匹配数
 *
 * 所以这个题目是复习匈牙利算法？
 * 怎么就WA了呢（）
 * 
 * 对于每一组数据，我操？
 * 我仏了还有哪里搞错了吗==
 * 怎么还能MLE的？
 * 
 * vis数组的必要性：在递归链中，避免间隔后末端使用前端的占用
 * 
 * 两个错误：
 * + 忽略递归链调用————visit数组的必要性；
 * + 寻找增广路时，之前扫过的部分不可跳过；
 */
#include <iostream>
#include <cstring>

#define indegree(x) (graph[0][x])
#define outdegree(x) (graph[x][0])

using namespace std;
typedef int boy;
typedef int girl;

int K,M,N;
int a,b;
int graph[505][505]{0};
bool visit[505]{0};         /*必要*/

girl match[550]{0};
boy couple[550]{0};

void initialArrays()
{
    memset(graph,0,sizeof(graph));
    memset(match,0,sizeof(match));
    memset(couple,0,sizeof(couple));
}

inline void addEdge(girl a, boy b)
{
    graph[a][b] = 1;
    // ++graph[a][0];
    // ++graph[0][b];
}

bool nextMatch(girl x)
{
    for(int i=1;i<=N;++i)       /*不可跳跃*/
        if(graph[x][i]&&!visit[i])
        {
            visit[i] = true;
            if(!match[i]||nextMatch(match[i]))
            {
                couple[x] = i;
                match[i] = x;
                return true;
            }
        }
    return false;
}

inline int maxMatch()
{
    int matched = 0;
    for(int i=1;i<=M;++i)
        if(!couple[i])
        {
            memset(visit,0,sizeof(visit));
            if(nextMatch(i))
                ++matched;
        }
    return matched;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>K&&K)
    {
        cin>>M>>N;
        initialArrays();

        for(int i=0;i<K;++i)
        {
            cin>>a>>b;
            addEdge(a,b);
        }

        cout<<maxMatch()<<endl;
    }
   
    return 0;
}