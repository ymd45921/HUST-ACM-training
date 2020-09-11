/**
 *
 * 又是有趣的博弈论
 *
 * 非极端情况下，一定会避免极端情况的出现
 * 所以绝对不会一次取很多让某一堆特别多，而是会一个个的取
 * 并且总是从当前可选择的数量最多的堆中取
 * 所以石子一定会被取完。
 *
 * 甚至还可以模拟 ==
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
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

int a[105];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), sum = 0;
        for (int i = 1; i <= n; ++ i)
            sum += a[i] = nextInt();
        sort(a + 1, a + n + 1);
        if (n == 1 || a[n] > sum - a[n])
        {
            puts("T");
            continue;
        }
        puts(sum % 2 ? "T" : "HL");
    }
    
    return 0;
}