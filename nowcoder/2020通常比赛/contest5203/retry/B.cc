/**
 *
 * B使用bitset的版本实现
 * 是没有用过的STL，得用用看
 * 
 * 更快，更美，更优雅
 */
#include <iostream>
#include <bitset>
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
const int mod = 3600;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, a[N]; cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i], a[i] %= mod;
        bitset<mod> img, msk;
        for (int i = 1; i <= n; ++ i)
        {
            msk.reset(); msk.set(a[i]);
            msk |= (img << a[i]) | (img >> mod - a[i]);
            img |= msk;
            if (img.test(0)) break;
        }
        cout << (img.test(0) ? "YES" : "NO") << endl;
    }

    return 0;
}