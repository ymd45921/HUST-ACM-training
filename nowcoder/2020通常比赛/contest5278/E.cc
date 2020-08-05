/**
 *
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

const int N = 1e5 + 5;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a[N];
    longs maxx = 0, disc = 0;
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> a[i], maxx += a[i];
    disc = (n + 1ll) * n / 2ll - n;
    cout << maxx - disc;

    return 0;
}