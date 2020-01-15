/**
 * 二分图最大匹配
 * König定理：最小覆盖点数=最大匹配数
 *
 * 所以这个题目是复习匈牙利算法？
 * 怎么就WA了呢（）
 * 
 * 对于每一组数据，我操？
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

girl match[550]{0};
boy couple[550]{0};

inline void initialArrays()
{
    memset(graph,0,sizeof(graph));
    memset(match,0,sizeof(match));
    memset(couple,0,sizeof(couple));
}

inline void addEdge(girl a, boy b)
{
    graph[a][b] = 1;
    ++graph[a][0];
    ++graph[0][b];
}

inline bool nextMatch(girl x)
{
    for(int i=couple[x]+1;i<=N;++i)
        if(graph[x][i])
            if(!match[i]||nextMatch(match[i]))
            {
                couple[x] = i;
                match[i] = x;
                return true;
            }
    return false;
}

inline int maxMatch()
{
    int matched = 0;
    for(int i=1;i<=M;++i)
        if(nextMatch(i))++matched;
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