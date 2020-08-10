/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

#define CEIL(a, b) ((a) / (b) + bool((a) % (b)))

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

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        for (int i = 0; i < n; ++ i)
            a[i] = nextInt();
        auto h = a[0], sum = a[0];
        for (int i = 1; i < n; ++ i)
            sum += a[i], h = max(h, CEIL(sum, i + 1));
        printf("%lld\n", h);
    }

    return 0;
}