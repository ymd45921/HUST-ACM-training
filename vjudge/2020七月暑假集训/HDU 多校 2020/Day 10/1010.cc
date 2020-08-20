/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <array>
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

uint pile[4][4];

bool check(int i, int j)
{
    for (int x = 1; x <= 3; ++ x)
        for (int y = 1; y <= 3; ++ y)
            if (x == i || y == j) continue;
            else
            {
                int a = 6 - i - x, b = 6 - j - y;
                uint xx = pile[a][b];
                for (int u = 1; u <= 3; ++ u)
                    for (int v = 1; v <= 3; ++ v)
                        if ((u == i && v == j) ||
                            (a == u && v == b) ||
                            (x == u && v == y)) continue;
                        else xx ^= pile[u][v];
                if (!xx) return false;
            }
    return true;
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        uint x_sum = 0, ans = 0;
        for (int i = 1; i <= 3; ++ i)
            for (int j = 1; j <= 3; ++ j)
                x_sum ^= pile[i][j] = nextInt();
        for (int i = 1; i <= 3; ++ i)
            for (int j = 1; j <= 3; ++ j)
                ans += check(i, j);
        printf("%u\n", ans);
    }

    return 0;
}