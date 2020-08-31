/**
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const longs mod = 998244353;
const int N = 1e5 + 5;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

namespace FastC
{
    const longs mod = ::mod;
    longs fact[N], inv[N];

    longs fastPow(longs a, longs b)
    {
        longs ans = 1;
        while (b)
        {
            if (b & 1) ans = (ans * a) % mod;
            a = (a * a) % mod;
            b >>= 1;
        }
        return ans % mod;
    }

    void init(int p)
    {
        fact[0] = 1;
        for (int i = 1; i <= p; i++)
            fact[i] = fact[i - 1] * i % mod;
        inv[p] = fastPow(fact[p], mod - 2);
        for (int i = p - 1; i >= 0; i--)
            inv[i] = inv[i + 1] * (i + 1) % mod;
    }

    longs $C(longs n, longs m)
    {
        if (m > n) return 0;
        return fact[n] * inv[m] % mod * inv[n - m] % mod;
    }

}

longs $less(int n, int m)
{
    using FastC::fastPow;
    auto res = fastPow(m - 1, n);
    res += (n & 1 ? -1 : 1) * (m - 1);
    if (res < 0) res += mod;
    return res % mod;
}

longs lucas(longs n, longs m)
{
    return !m ? 1 :
           FastC::$C(n % mod, m % mod) *
           lucas(n / mod, m / mod) % mod;
}

longs solution(int n, int k)
{
    using FastC::$C;
    longs ans = 0;
    for (int i = 1; i <= k; ++ i)
    {
        ans = (ans + (((k - i) & 1) ? -1 : 1) * $C(k, i) * $less(n, i));
        if (ans < 0)
        {
            auto cnt = ans / mod;
            cnt = 1 - cnt;
            ans += cnt * mod;
        }
        ans %= mod;
    }
    return ans;
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, n, k; cin >> t;
    FastC::init(1e5);
    while (t --)
    {
        cin >> n >> k;
        if (k == 1) cout << (n == 1 ? 1 : 0) << endl;
        else cout << solution(n, k) % mod << endl;
    }

    return 0;
}