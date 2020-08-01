/**
 * n > 0
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
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, l, r, m;
    cin >> t;
    while (t --)
    {
        cin >> l >> r >> m;
        auto del = r - l;
        for (int ii = l; ii <= r; ++ ii)
        {
            auto p = m % ii, n = (m / ii + 1) * ii - m;
            if (m / ii && p <= del) { cout << ii << ' ' << ii + p << ' ' << ii << endl; break; }
            else if (n <= del) { cout << ii << ' ' << ii << ' ' << ii + n << endl; break; }
        }
    }

    return 0;
}