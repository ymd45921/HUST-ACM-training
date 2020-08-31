/**
 *
 * RE???
 * 全局变量的锅
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 1e5 + 5;
int t, n, x, a[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> t; while (t --)
    {
        cin >> n >> x;
        for (int i = 1; i <= n; ++ i) cin >> a[i];
        sort(a + 1, a + 1 + n);
        longs ans = 0, sum = a[n], lim = x, cur = n - 1;
        while (sum >= lim)
        {
            sum += a[cur], lim += x;
            ++ ans; -- cur;
            if (!cur) break;
        }
        if (!cur && sum >= lim) ++ ans;
        cout << min(ans, (longs)n) << endl;
    }

    return 0;
}