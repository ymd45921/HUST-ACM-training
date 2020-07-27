/**
 *
 * 整个一憨批，理解了错误的等价行动想了两个小时
 *
 * multi-drop-2 就相当于环形数组取一个数插入任意位置
 * 可以取一个最长上升子序列，然后 rearrange 其他数字
 * 这个需要 rearrange 的数字的数目就是答案；
 * 
 * 为什么这个 LIS 它 WA 了（
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
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 505;
int p[N], a[N], f[N], cnt;

int main()
{
    const int n = nextInt();
    int st = cnt = 0, lis = 0;
    for (int i = 0; i < n; ++ i)
        p[i] = nextInt(), p[i] == 1 && (st = i);
    for (int i = 0; i < n; ++ i)
        a[i] = p[(st + i) % n];
    memset(f, 0x3f, sizeof f);
    for (int i = 0; i < n; ++ i)
        if (!cnt || f[cnt - 1] < a[i])
            f[cnt ++] = a[i], lis = max(lis, cnt);
        else *lower_bound(f, f + cnt, a[i]) = a[i];
    cout << n - lis << endl;
    return 0;
}