/**
 * 
 * 这难道是一个最小生成树的题目吗
 */
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

const int N = 505;
longs n, dis[N][N];
longs a, b, c, node;
priority_queue<pair<longs,longs>> q;
bool intree[N];
map<longs,longs> m[N];

inline longs offset(int aa, int bb, int cc)
{
    return dis[aa][bb]+dis[aa][cc]-(dis[bb][cc]>>1);
}

inline longs edge(int aa, int bb, longs cc)
{
    return dis[aa][bb]=dis[bb][aa]=m[aa][bb]=m[bb][aa]=cc;
}

bool walk(longs from, longs to, longs )

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    return 0;
}