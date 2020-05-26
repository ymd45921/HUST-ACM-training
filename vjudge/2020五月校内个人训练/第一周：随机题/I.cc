/**
 *
 * emmm…… 怎么还有这么简单的做法
 * 已知有线段树做法
 *
 * 其实是求一个最大可偏移的距离
 * 转移方法：猜 x 之前最远不能到这里
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 1e5 + 5;
int a[N], lb[N], rb[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++ i)
        cin >> a[i];
    if (n <= 1) cout << 0 << endl;
    else
    {
        for (int i = m - 1; i >= 0; -- i)
        {
            rb[(n + a[i] - i) % n] = rb[(n + a[i] - i - 1) % n] + 1;
            lb[(n + a[i] + i) % n] = lb[(n + a[i] + i + 1) % n] + 1;
        }
        longs ans = 0;
        for (int i = 0; i < n; ++ i)
            ans += min(n, i + m + 1 - rb[i]) - max(1, i - m - 1 + lb[i]) + 1;
        cout << ans << endl;
    }
    return 0;
}