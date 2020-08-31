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
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

int main()
{
    auto h1 = nextInt(), m1 = nextInt(), s1 = nextInt();
    auto h2 = nextInt(), m2 = nextInt(), s2 = nextInt();
    auto $1 = h1 * 3600 + m1 * 60 + s1;
    auto $2 = h2 * 3600 + m2 * 60 + s2;
    cout << abs($1 - $2);

    return 0;
}