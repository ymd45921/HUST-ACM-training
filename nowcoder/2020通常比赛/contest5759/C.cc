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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, k;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        n -= k;
        cout << ((n >= 2 * k && n % 2 == 0) ? "Yes" : "No") << endl;
    }

    return 0;
}