#include <iostream>
#include <cstdio>
#include <cstring>

#define toChar(x) ('0' + x)
#define cur [st][ed][pos][x]   // 当前函数处理的位置

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

const int N = 45;
const int M = 405;
const int INF = 0x3f3f3f3f;

int n,m;
char s[N][M];
int best[N][N][M][10];          // 最优修改次数，初值INF
int split[N][N][M][10];         // 修改标签，初值是0

int recurse(int st, int ed, int pos, int x)     // 将第[st,ed)个数字的第pos位改为x后，生成有效答案的最少步数
{
    if (pos >= m || st == ed) return 0;         // 参数无效：无贡献
    if (x >= 10) return INF;                    // 不可能的情况：返回INF
    int & that = best cur;
    if (that < INF) return that;                // 记忆化搜索

    int cost = 0;                               
    for (int k = st; k <= ed; ++k)              // 尝试修改区间内所有分界点为 x
    {
        int now = cost                          // 当前的费用 = 修改当前位的费用 + 维护两个区间的有效性的费用
                  + recurse(st, k, pos+1, 0)    
                  + recurse(k, ed, pos, x+1);   
        if (now < that)                         // 更新最小费用和分界标签
        {
            split cur = k;          
            that = now;
        }
        if (k < ed)                             
            cost += (s[k][pos] != toChar(x));   // 这次的修改在区间内且是有效更改，累加步数
    }
    return that;
}

void remake(int st, int ed, int pos, int x)     // 利用split还原最优方案，以修改原数组     
{
    if (x >= 10 || pos >= m || st == ed)        // 无效参数
        return;
    int & val = split cur;

    for (int i = st; i < val; ++ i)             
        s[i][pos] = toChar(x);                  // 根据标签的指示修改
    remake(st, val, pos+1, 0);                  
    remake(val, ed, pos, x+1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    for (int i=0;i<n;++i)
        cin>>s[i];
    memset(best,0x3f,sizeof(best));

    cerr<<"COST: "<<recurse(0,n,0,0)<<endl;     // cerr输出最优步数
    remake(0,n,0,0);

    for (int i=0;i<n;++i)
        cout<<s[i]<<endl;
    return 0;
}