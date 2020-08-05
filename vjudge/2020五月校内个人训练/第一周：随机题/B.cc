/**
 *
 */
#include <iostream>
#include <algorithm>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

longs solve(longs a, longs k)
{
    auto ans = a;
    while (-- k)
    {
        auto b = ans;
        longs big = 0, small = 10;
        while (b > 0)
        {
            big = max(big, b % 10);
            small = min(small, b % 10);
            b /= 10;
        }
        if (!small) break;
        else ans += big * small;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    longs a, k;
    cin >> t;
    while (t --)
    {
        cin >> a >> k;
        cout << solve(a, k) << endl;
    }

    return 0;
}