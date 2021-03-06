/**
 *
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
        int a = nextInt(), b = nextInt(), k = nextInt();
        auto d = abs(a - b), mi = min(a, b), ma = max(a, b);
        if (d <= k) { puts("1"); continue; }
        if (d == k + 1) { puts(mi == 1 ? "0" : "1"); continue; }
        if (mi == k + 2 || d <= 2 * k + 1) { puts("1"); continue; }

    }

    return 0;
}