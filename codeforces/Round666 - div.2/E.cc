/**
 * 
 * 
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e6 + 5;
int a[N];

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt(), r1 = nextInt(), r2 = nextInt(),
        r3 = nextInt(), d = nextInt();
    for (int i = 1; i <= n; ++ i) a[i] = nextInt();
    

    return 0;
}
