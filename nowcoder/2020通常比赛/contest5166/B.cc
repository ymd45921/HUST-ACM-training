/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;
typedef int __int;

#define int longs

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int gg[21], mm[21];

longs _fact(int n)
{
    if (!n) return 0;
    longs a = 1;
    while (n --) a *= n;
    return a;
}

longs _A(int n, int m)
{
    if (!n) return 0;
    longs a = 1;
    while (m --) a *= n--;
    return a;
}

longs _C(int n, int m)
{
    return _A(n,m) / _fact(m);
}

__int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    memset(gg, 0, sizeof gg);
    memset(mm, 0, sizeof mm);

    auto solve = [&](int i) -> longs
    {
        longs xx = max(gg[i], mm[i]);
        longs yy = min(gg[i], mm[i]);
        return xx * yy;
    };

    int n, t;
    cin >> n;
    while (n --)
    {
        cin >> t;
        t >= 0 ? ++gg[t] : ++mm[-t];
    }
    longs ans = gg[0]*(gg[0]-1)/2;
    for (int i = 1; i <= 20; ++ i)
        ans += solve(i);
    cout << ans << endl;

    return 0;
}