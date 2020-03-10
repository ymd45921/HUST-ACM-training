/**
 *
 * DP 来写的话是真的会死人的
 * 但是并不是没有其他的办法
 *
 */

#include <iostream>
#include <cstdio>
#include <cstring>

#define var() (n*m + 47)        // 相当于是INF值，意义不明
#define toChar(x) ('0' + x)
#define pin [st][ed][pos][x]

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

const int N = 45;
const int M = 405;

int n,m;
char s[N][M];
int best[N][N][M][10];          // 最佳修改次数，由recurse求解并且更新，初值var
int split[N][N][M][10];         // 修改标签，recurse更新，remake使用，初值是0

int var;

int recurse(int st, int ed, int pos, int x) // 将第[st,ed)个数字的第pos位改为x后，生成有效答案的最少步数
{
    if (pos >= m || st == ed) return 0;         // 这样的区间一定维护了有序性，参数无效，无贡献
    if (x >= 10) return var;                    // 不可能的情况：返回INF
    int & that = best[st][ed][pos][x];
    if (that < var) return that;                // 记忆化搜索：已经求过了值

    int cost = 0;                               // 初始化修改步数：这个cost只包括了[st,k]上第pos个数修改的费用，所以需要累加
    for (int k = st; k <= ed; ++k)              // 尝试区间内所有可用的分界点k
    {
        int now = cost                          // 当前的费用 = 修改当前位的费用 + 维护两个区间的有效性的费用
                  + recurse(st, k, pos+1, 0)    // 前半段已修改高位：[st,k)区间内的最高位必然小
                  + recurse(k, ed, pos, x+1);   // 后半段尝试更大数：[k,ed)区间内的最高位至少要比前半端大1
        if (now < that)                         // 更新最小费用
        {
            split[st][ed][pos][x] = k;          // 更新记录的分界点：在此处分界是可以获得最小费用方案的一部分
            that = now;
        }
        if (k < ed)                             // 分界点仍然在有效区间内，更新步数
            cost += (s[k][pos] != toChar(x));   // 尝试修改[st,k]上的第k个数的第pos位，而且是有效更改，则累加步数
    }
    return that;
}

void remake(int st, int ed, int pos, int x) // 利用split模拟最优方案，基于此方案修改原数组     
{
    if (x >= 10 || pos >= m || st == ed)        // 无效参数
        return;
    int & val = split[st][ed][pos][x];

    for (int i = st; i < val; ++ i)             // 分界点是默认值时不修改
        s[i][pos] = toChar(x);                  // 根据标签的指示修改
    remake(st, val, pos+1, 0);                  // 递归地修改分段
    remake(val, ed, pos, x+1);
}

inline void init()
{
    var = var();
    for (int i = 0; i <= n; ++ i)
        for (int j = 0; j <= n; ++ j)
            for (int k = 0; k <= m; ++ k)
                for (int l = 0; l < 10; ++ l)
                    best[i][j][k][l] = var;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    for (int i=0;i<n;++i)
        cin>>s[i];
    init();
    cerr<<"COST: "<<recurse(0,n,0,0)<<endl;
    remake(0,n,0,0);
    for (int i=0;i<n;++i)
        cout<<s[i]<<endl;
    return 0;
}