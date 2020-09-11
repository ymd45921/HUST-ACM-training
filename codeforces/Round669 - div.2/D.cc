/**
 *
 * 复习一下单调栈：可以找到某一侧比它大 / 小的数字
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

const int N = 1e5 + 50;
longs h[N];

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        h[i] = nextInt();
    
    return 0;
}