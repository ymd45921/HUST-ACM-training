/**
 *
 *
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
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 3e5 + 5;
int a[N];

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt(), q = nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = nextInt();
    while (q --)
    {
        int x = nextInt(), y = nextInt();
        
    }


    return 0;
}

