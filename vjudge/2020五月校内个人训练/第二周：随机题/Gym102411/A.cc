/**
 *
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

    int a, b, n;
    cin >> a >> b >> n;
    auto xx = n - a;
    auto tt = xx / (b - a) + bool(xx % (b - a));
    cout << tt * 2 - 1 << endl;

    return 0;
}