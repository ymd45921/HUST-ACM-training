/**
 * 原题号： CF 1236E
 *
 * 思路：
 * - 显然，从某个点出发可以到达的终点构成了一个连续的区间
 * - 所以，问题转化成从起点出发最远可达的左右端点
 * - 向某方向前进时会因为当前位置冲突而停止一格
 * - 停留之后，相当于它左边那个格子走过来没有停，可以直接转移
 * - 统计 X[i] 表示向某方向行走的时候，因障碍止步的次数
 * - 统计方法：可以倒过来统计，a[i] 会影响到：
 *   - 如果向右：从 a[i] - i 位置看来有阻碍
 *   - 根据上面讨论的递推关系，可以直接由 a[i] - i - 1 转移
 *   - 统计步数是数组初值是 0，不用考虑前面阻碍的影响
 * - 可以开三倍数组考虑偏移；
 *
 * 特别注意：询问开始前可以进行移动；所有的询问结束了还可以移动一次
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 1e5 + 5;
const int off = 1e5;

int a[N], lb[3 * N], rb[3 * N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin >> n >> m;
    for (int i = 1; i <= m; ++ i)
        cin >> a[i];
    if (n <= 1) cout << 0 << endl;
    else
    {
        for (int i = m; i >= 1; -- i)
        {
            rb[off + a[i] - i] = rb[off + a[i] - i - 1] + 1;
            lb[off + a[i] + i] = lb[off + a[i] + i + 1] + 1;
        }
        longs cnt = 0;
        for (int i = 1; i <= n; ++ i)
            cnt += min(n, i + (m + 1) - rb[off + i]) - max(1, i - (m + 1) + lb[off + i]) + 1;
        cout << cnt << endl;
    }

    return 0;
}