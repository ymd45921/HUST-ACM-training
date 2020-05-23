/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 2e5 + 5;
int e[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n; cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 0; i < n; ++ i) cin >> e[i];
        sort(e, e + n);
        int ans = 0, lst = 0, res = 0;
        for (int i = 1; i < n; ++ i)
            if (e[i] > e[i - 1])
            {
                auto xx = res + i - lst;
                ans += xx / e[lst];
                res = xx % e[lst];
                lst = i;
            }
        auto xx = res + n - lst;
        ans += xx / e[lst];
        cout << ans << endl;
    }

    return 0;
}