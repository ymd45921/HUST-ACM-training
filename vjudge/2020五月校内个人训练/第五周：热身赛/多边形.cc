/**
 *
 * 数多边形里的对角线的交点数：
 * 题目的条件必然实在简化什么——
 * 比起一层一层的向内数，可能需要分情况讨论
 *
 * 不妨：对角线 = 两条线的交点 = 四个不同的点
 * 问题迎刃而解。
 * 
 * 小问题：不要随便提前除法，毕竟整除不是分数除法
 * 排列组合都忘记了吗（
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, x; cin >> t;
    while (t --)
    {
        cin >> x;
        longs ans = (longs) x * (x - 1)* (x - 2) * (x - 3) / 24 ;
        cout << ans << endl;
    }

    return 0;
}