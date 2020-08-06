/**
 * 这是来自群友的 CSDN 的做法：
 * https://blog.csdn.net/ding_ning123/article/details/107784591
 * 
 * - 设三个数字中最小的数字是 a，拆分成 m 个数字
 * - 设小中大三个数字分别有 bi 个，则 n = a * m + b2 + b3 * 2
 * - 对于确定的 a 和 m，有答案的 n 的区间是 [a * m + 3, (a + 2) * m - 3]
 * - 然后经过神秘打表，就可以找到在隔项差分数组上的规律
 * 
 * 然后这个题目就做出来了（神仙
 * 注意：这里说的隔项差分数组指的是在差分数组上的隔项差分；
 * 有点想知道这样做的一个合理性以及思考回路（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 5;
longs f[N * 3], sum[N];

void preProcess()
{
    for (int m = 3; m < N; ++ m)
        for (int am = m; am < N; am += m)
            ++ f[am + 3], ++ f[am + 2 * m], 
            -- f[am + m + 1], -- f[am + m + 2];
    for (int i = 3; i < N; ++ i) f[i] += f[i - 2];
    for (int i = 1; i < N; ++ i) f[i] += f[i - 1];
    for (int i = 1; i < N; ++ i) sum[i] = sum[i - 1] + f[i];
}

int main()
{
    ios::sync_with_stdio(false);
    
    preProcess();
    int t = nextInt();
    for (int i = 1; i <= t; ++ i)
    {
        int l = nextInt(), r = nextInt();
        printf("Case #%d: %lld\n", i, sum[r] - sum[l - 1]);
    }
    
    return 0;
}