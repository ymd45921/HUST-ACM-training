/**
 *
 * 就是贪心暴力
 * 只是直接遍历求和太慢了，但是可以用前缀和
 * 二分下次的位置，加速暴力
 */
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 2e5 + 5;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, a[N], q, t, inm = 0, sum[N] {0};
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i], inm = max(inm, a[i]),
        sum[i] = sum[i - 1] + a[i];
    unordered_map<int, int> mem;
    const auto end = sum + n + 1;
    cin >> q; while (q --)
    {
        cin >> t;
        if (t < inm) cout << "Impossible" << endl;
        else if (mem.count(t)) cout << mem[t] << endl;
        else
        {
            int ans = 0;
            for (int cur = 0; cur < n; -- cur)
            {
                ++ ans;
                cur = upper_bound(sum + cur, end, sum[cur] + t) - sum;
            }
            cout << (mem[t] = ans) << endl;
        }
    }

    return 0;
}