/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, hp, atk, h, a;
    auto solve = [&]() -> int
    {
        int xx = h / atk;
        int yy = h - xx*atk;
        int tt = yy ? xx : xx-1;
        int dmg = a*tt;
        cerr << dmg << endl;
        if (!dmg) return -1;
        else return hp%dmg ? hp/dmg : hp/dmg-1;
    };

    cin >> t;
    while (t --)
    {
        cin >> hp >> atk >> h >> a;
        cout << solve() << endl;
    }

    return 0;
}