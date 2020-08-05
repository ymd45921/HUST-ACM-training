/**
 *
 * 傻逼玩意写半天。吐了
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t, n, p, c, pp, cc;
    cin >> t; while (t --)
    {
        cin >> n;
        bool flag = true;
        pp = -1, cc = -1;
        while (n --)
        {
            cin >> p >> c;
            if (p < c) flag = false;    // 瞎
            if (!~pp && !~cc)
            {
                pp = p, cc = c;
                continue;
            }
            if (p - pp < c - cc ||
                p - pp < 0 ||
                c - cc < 0
            ) flag = false;
            pp = p, cc = c;
        }
        cout << (flag ? "YES" : "NO") << endl;
    }

    return 0;
}