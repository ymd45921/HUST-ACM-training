/**
 *
 * 还是stn……
 */
#include <iostream>
#include <algorithm>
#include <cstring>

#define hp first
#define ex second

using namespace std;
typedef long long longs;
using monster = pair<longs, longs>;

const auto inf = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int N = 3e5 + 5;

int t, n;
longs c[N];
monster m[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> t; while (t --)
    {
        cin  >> n;
        for (int i = 0; i < n; ++ i)
            cin >> m[i].first >> m[i].second;
        longs sum = c[0] = max(0ll, m[0].hp - m[n - 1].ex);
        for (int i = 1; i < n; ++ i)
            sum += c[i] = max(0ll, m[i].hp - m[i - 1].ex);
        longs ans = inf;
        for (int i = 0; i < n; ++ i)
        {
            auto tmp = sum - c[i] + m[i].hp;
            ans = min(ans, tmp);
        }
        cout << ans << endl;
    }

    return 0;
}