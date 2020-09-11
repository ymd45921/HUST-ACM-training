/**
 * 贪心
 *
 * 因为前面减少是免费的，后面增加是免费的，所以尽量向两侧靠拢
 * 最后就是一个前缀和的最小值 / 后缀和的最大值（绝对值）
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

const int N = 1e5 + 5;
int a[N], n, t;
longs sum[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n, sum[0] = 0;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i], sum[i] = sum[i - 1] + a[i];
        longs ans = 0;
        for (int i = 1; i <= n; ++ i)
            ans = min(ans, sum[i]);
        cout << abs(ans) << endl;
    }

    return 0;
}