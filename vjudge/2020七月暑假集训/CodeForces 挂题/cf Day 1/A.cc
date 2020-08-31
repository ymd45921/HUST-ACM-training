/**
 *
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
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, t, d;
    cin >> t;
    while (t --)
    {
        cin >> n >> d;
        if (n >= d) cout << "YES" << endl;
        else
        {
            auto x = sqrt(d) - 1;
            auto c = x + ceil(d / (ceil(x) + 1)) <= n;
            auto f = x + ceil(d / (floor(x) + 1)) <= n;
            cout << (c || f ? "YES" : "NO") << endl;
        }
    }

    return 0;
}