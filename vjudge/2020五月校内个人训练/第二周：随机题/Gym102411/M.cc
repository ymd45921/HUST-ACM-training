/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <unordered_map>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 2060;
int n, t, a[N];
unordered_map<int, int> mmp;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> t; while (t --)
    {
        cin >> n;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];
        auto n1 = n - 1;
        longs ans = 0;
        for (int i = 1; i <= n; ++ i)
            ++ mmp[a[i]];
        for (int i = 1; i <= n; ++ i)
        {
            -- mmp[a[i]];
            for (int j = 1; j < i; ++ j)
            {
                auto pos = 2 * a[i] - a[j];
                ans += mmp[pos];
            }
        }
        cout << ans << endl;
    }


    return 0;
}