/**
 * 二分图
 *
 */
#include <iostream>
#include <vector>

using namespace std;
struct boy
{
    int num;int* indegree;
    bool operator<(const boy& rhs) const;
};
struct girl
{
    int num;int* outdegree;
    bool operator<(const girl& rhs) const;
};

int K,M,N;
int a,b;
int outdegree[550]{0};
vector<boy> edgelist[505];

inline void addEdge(int a, int b)
{
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>K>>M>>N;
    for(int i=0;i<K;++i)
    {
        cin>>a>>b;

    }
    cin>>a;

}