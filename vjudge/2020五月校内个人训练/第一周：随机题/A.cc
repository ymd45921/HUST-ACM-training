/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

int solve(int a, int b, int c)
{
    auto x = min(b / 2 - c / 4, a);
    if (x < 0) x = 0;
    auto y = min(c / 2, b - x * 2);
    if (y < 0) y = 0;
    return (x + y) * 3;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, a, b, c;
    cin >> t;
    while (t --)
    {
        cin >> a >> b >> c;
        cout << solve(a, b, c) << endl;
    }


    return 0;
}