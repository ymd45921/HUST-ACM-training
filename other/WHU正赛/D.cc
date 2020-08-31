/**
 *
 * 离谱，快速幂就过了
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
const int N = 1e5+5;
const int mod = 1e9+7;

int t, n, m;
int a[N];

longs _fact(longs n)
{
    if (!n) return 1;
    longs a = 1;
    while (n) a *= n --;
    return a;
}

longs _A(longs n, longs m)
{
    if (!n) return 0;
    else if (!m) return 1;
    longs a = 1;
    while (m --) a *= n --;
    return a;
}

longs _C(longs n, longs m)
{
    return _A(n,m) / _fact(m);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto fun = [&](longs nn)
    {
        longs tmp = 1;
        while (nn > 30)
        {
            tmp = (tmp << 30) % mod;
            nn -= 30;
        }
        return (tmp << nn) % mod;
    };

    auto another = [&](longs nn)
    {
        if (!nn) return 1ll;
        longs ans = 1, xx = 2;
        while (nn)
        {
            if (nn & 1) ans = (ans * xx) % mod;
            xx = (xx * xx) % mod;
            nn >>= 1;
        }
        return ans % mod;
    };

//    freopen("D:\\shiroha\\Source\\Repos\\HUST-ACM-training\\other\\WHU正赛\\fun.txt", "w", stdout);
//    for (int i = 0; i < mod; ++ i)
//        cout << fun(i) << ", " << endl;
//    return 1;

    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        if (!m) cout << 0 << endl;
        longs nn =  n - 1;
        longs tt = m;
        longs ans = 0;
        ans += another(nn);
        ans *= tt; ans %= mod;
        cout << ans << endl;
    }

    return 0;
}