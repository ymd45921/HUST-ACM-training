/**
 * 真就暴力呗？
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>

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

const int N = 1e5 + 5, M = 1e9 + 7;
int a[N];

longs calculate(int n, longs round)
{
    longs cost = 0, now = 1;
    for (int i = 0; i < n; ++ i, now *= round)
        cost += llabs(a[i] - now);
    return cost;
}

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt();
    longs ans = 0x7fffffffffffffff;
    for (int i = 0; i < n; ++ i)
        a[i] = nextInt();
    sort(a, a + n);
    for (int p = 1; p < M; ++ p)
    {
        longs now = 1, cost = 0;
        for (int i = 0; i < n && cost < ans; ++ i, now *= p)
            cost += llabs(a[i] - now);
        if (cost < ans) ans = cost;
        else break;
    }
    printf("%lld\n", ans);

    return 0;
}