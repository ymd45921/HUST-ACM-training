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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs t, a, b;
    cin >> t;
    while (t --)
    {
        cin >> a >> b;
        int cnt = -1, bb = b + 1;
        while (bb) bb /= 10, ++ cnt;
        cout << max(0, cnt) * a << endl;
    }

    return 0;
}