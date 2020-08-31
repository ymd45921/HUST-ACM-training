/**
 *
 * 好强啊……只需要参考这两篇题解就好了：
 * https://www.luogu.com.cn/problem/solution/CF1270G
 *
 * 害，就算有了这样的思路，实现也非常的蠢：
 * - 不用递归，迭代就够了；
 * - 不用考虑森林：内向基环要不联通要不自己就是环；
 * - 就算是递归，退出一层时应记得弹栈；
 * 感觉还是基环内向森林的代码写少了啊== 森林里没有树只有环
 *
 * TLE 原因：使用 C++ IO？这个题也卡快读吗
 */
#define USING_STDIO 1
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

const int N = 1e6 + 5;
int to[N], vis[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t = nextInt(), n;
    while (t --)
    {
        n = nextInt();
        for (int i = 1; i <= n; ++ i)
            to[i] = i - nextInt(), vis[i] = 0;
        int now = 1, st;
        while (!vis[now]) vis[now] = 1, now = to[now];      // 找到环内的一点
        vector<int> ans;
        st = now, now = to[now];
        while (now != st) ans.push_back(now), now = to[now];
        ans.push_back(st);
        printf("%d\n", (int)ans.size());
        for (auto &ii : ans) printf("%d ", ii);
        puts("");
    }

    return 0;
}