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

const int N = 1e5 + 5;
uint a[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    uint n, m = 1e9 + 7, l = -N, d = N;
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> a[i], m = min(m, a[i]);
    for (int i = 0; i < n; ++ i)
        if (a[i] == m) d = min(d, i - l), l = i;
    cout << d << endl;

    return 0;
}