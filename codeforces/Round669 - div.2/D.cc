/**
 *
 * 动态规划：
 * - 可以从 i 起跳到达 j
 * - f[i] 为转移的起点
 *
 * 复习一下单调栈：可以找到某一侧比它大 / 小的数字
 * 单调栈和单调队列的区别：栈只能知道它一侧的第一个 cmp 它的元素
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <functional>
#include <stack>

using namespace std;
using longs = long long;
using uint = unsigned;

#define REPEAT_I for (int i = 1; i <= n; ++ i)
#define END_REPEAT
#define eprintf(x...) fprintf(stderr, x)
#define eputs(s) fputs(s, stderr)

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 50;
longs h[N];
int f[N], big[N], small[N];

using increase = less<longs>;
using decrease = greater<longs>;

template <class _compare>
void runMonoStack(int n, int* arr)
{
    stack<int> s;
    _compare cmp;
    s.push(1);
    for (int i = 2; i <= n; ++ i)
    {
        while (!s.empty() && !cmp(h[s.top()], h[i]))
        {
            arr[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) arr[s.top()] = -1, s.pop();
}

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        h[i] = nextInt();
    big[1] = small[1] = 1;
    for (int i = 1; i <= n; ++ i)
        f[i] = i - 1;
    runMonoStack<increase>(n, small);
    runMonoStack<decrease>(n, big);
    REPEAT_I eprintf("%d ", big[i]);
    END_REPEAT eputs("\n");
    REPEAT_I eprintf("%d ", small[i]);
    END_REPEAT eputs("\n");
    for (int i = 2; i <= n; ++ i)
    {
        f[i] = min(f[i], f[i - 1] + 1);
        if (h[i - 1] > h[i])
            f[big[i - 1]] = min(f[big[i - 1]], f[i - 1] + 1);
        if (h[i - 1] < h[i])
            f[small[i - 1]] = min(f[small[i - 1]], f[i - 1] + 1);
    }
    printf("%d\n", f[n]);

    return 0;
}

