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

    longs t, l, r, m;
    cin >> t;
    while (t --)
    {
        cin >> l >> r >> m;
        auto del = r - l;
        for (int a = l; a <= r; ++ a)
        {
            auto pos = m % a, neg = (m / a + 1) * a - m;
            longs b, c;
            if (m / a > 0 && pos <= del) b = l + pos, c = l;
            else if (neg <= del) b = l, c = l + neg;
            else continue;
            cout << a << ' ' << b << ' ' << c << endl;
            break;
        }
    }

    return 0;
}