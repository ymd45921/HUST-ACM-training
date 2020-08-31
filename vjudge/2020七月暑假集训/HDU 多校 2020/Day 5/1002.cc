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

const int N = 1e6 + 5;
int s[N];

int main()
{
    ios::sync_with_stdio(false);

    int cases = nextInt();
    while (cases --)
    {
        int n = nextInt(), m = nextInt(), q = nextInt();
        for (int i = 0; i < n; ++ i) s[i] = nextInt();
        int last = 0;
        while (q --)
        {
            int t = nextInt(), c = last ^ nextInt(),
                i = last ^ nextInt();

        }
    }

    return 0;
}