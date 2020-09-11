/**
 * 构造题？脑瘫题！
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>

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

int p[120], n, t;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 1; i <= n; ++ i)
            cin >> p[i];
        for (int i = n; i; -- i)
            cout << p[i] << ' ';
        cout << endl;
    }

    return 0;
}