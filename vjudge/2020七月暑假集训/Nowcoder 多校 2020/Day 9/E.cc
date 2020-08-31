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

const longs mod = 998244353;

int main()
{
    ios::sync_with_stdio(false);

    int a = nextInt(), b = nextInt(),
        c = nextInt(), d = nextInt(),
        x = nextInt(), y = nextInt();
    

    return 0;
}