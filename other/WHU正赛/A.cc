/**
 *
 * sbsb
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const int N = 1e5+5;

int t, n, m;
int a[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        if (n == m || !m)
        {
            int me = a[0];
            sort(a, a+n);
            auto pos = lower_bound(a, a+n, me);
            cout << (n - (pos-a)) << endl;
            continue;
        }
        -- m; ++ a[0];
        sort(a+1, a+n);
        auto lb = lower_bound(a+1, a+n, a[0]-1);
        auto ub = upper_bound(a+1, a+n, a[0]-1);
        int xx = n - (ub-a); m -= xx;
        int yy = (lb-a) - 1; m -= yy;
        if (m <= 0) cout << xx + 1 << endl;
        else cout << xx + 1 + m << endl;
    }

    return 0;
}