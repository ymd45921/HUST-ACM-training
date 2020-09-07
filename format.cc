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

int main()
{
    ios::sync_with_stdio(false);


    return 0;
}
