/**
 *
 * ???
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

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        for (int i = 1; i <= n; ++ i)
            for (int j = i + 1; j <= n; ++ j)
                printf("%d %d\n", i, j);
    }

    return 0;
}