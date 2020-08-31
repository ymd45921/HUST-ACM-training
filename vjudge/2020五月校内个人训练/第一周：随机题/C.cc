/**
 *
 * 啊这，啊这，我是傻逼
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int mod = 1e9 + 7;

int fastPow(int a, int n)
{
    if (!a) return 0;
    else if (!n) return 1;
    longs now = a, ans = 1;
    unsigned b = n;
    while (b)
    {
        if (b & 1u) ans = ans * now % mod;
        now = now * now % mod;
        b >>= 1u;
    }
    return (int) ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    auto xx = fastPow(2, m);
    if (!xx) xx += mod;
    xx = (xx - 1) % mod;
    cout << fastPow(xx, n) << endl;

    return 0;
}