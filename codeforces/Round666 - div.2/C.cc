/**
 *
 * 有点东西，有意思嗷
 *
 * 是有趣的构造，其实题目的样例也给了暗示了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

#define eprintf(x ...) fprintf(stderr, x)

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

const int N = 1e5 + 5;
longs a[N];

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = nextInt();
    if (n == 1)
    {
        printf("1 1\n1\n1 1\n-1\n1 1\n%lld\n", -a[1]);
        return 0;
    }
    printf("%d %d\n", 1, n - 1);
    for (int i = 1; i < n; ++ i)
    {
        longs b = (n - 1) * a[i];
        printf("%lld ", b);
        a[i] += b;
    }
    for (int i = 1; i <= n; ++ i)
        eprintf("%lld ", a[i]);
    eprintf("\n");
    printf("\n%d %d\n%lld\n1 %d\n", n, n, -a[n], n);
    a[n] = 0;
    for (int i = 1; i <= n; ++ i)
        eprintf("%lld ", a[i]);
    eprintf("\n");
    for (int i = 1; i <= n; ++ i)
        printf("%lld ", -a[i]);
    puts("");

    return 0;
}