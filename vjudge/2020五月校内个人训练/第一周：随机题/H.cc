/**
 *
 * 确实好做
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s;
    cin >> n >> s;
    if (s >= 2 * n)
    {
        cout << "YES" << endl;
        auto xx = s / n;
        auto yy = s % n;
        for (int i = 1; i <= yy; ++ i)
            cout << xx + 1 << ' ';
        for (int i = yy + 1; i <= n; ++ i)
            cout << xx << ' ';
        cout << endl << 1 << endl;
    }
    else if (s <= n + 1) cout << "NO" << endl;
    else
    {
        auto xx = s - n + 1;
        auto yy = s - xx;
        if (xx - yy > 1)
        {
            cout << "YES" << endl;
            cout << xx << ' ';
            while (yy --) cout << 1 << ' ';
            cout << endl << xx - 1 << endl;
        }
        else cout << "NO" << endl;
    }

    return 0;
}