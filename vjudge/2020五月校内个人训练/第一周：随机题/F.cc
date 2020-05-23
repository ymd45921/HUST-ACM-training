/**
 *
 * 循环可以进一步优化
 * 
 * 说是说理论上是简单题，但是哪个统计方法我事后也没想出来
 * 还是自己不太行 ==
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 5e5 + 5;

longs solve(int a, int b, int c, int d)
{
    auto l = a + b, r = b + c;
    longs xx = b - a + 1, yy = c - b + 1;
    longs ans = 0;
    for (int i = l; i <= r; ++ i)
    {
        auto zz = i > d ? d - c + 1 : i - c;
        if (zz <= 0) continue;
        longs xy = max(0, i - a - b + 1);
        longs yx = max(b + c - i + 1, 0);
        ans += min(min(xy, yx), min(xx, yy)) * zz;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << solve(a, b, c, d) << endl;

    return 0;
}