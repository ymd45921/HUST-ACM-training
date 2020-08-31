/**
 *
 * 折纸：横向 x 次，纵向 y 次；然后横纵裁剪
 * 得到碎片数：(2^x + 1) * (2^y + 1)
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int mod = 998244353, N = 6e6 + 5;

ulongs fastPow(ulongs a, ulongs b)
{
    ulongs ans = 1;
    while(b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

ulongs inverse(ulongs a, ulongs p)
{
    if (a > p || a <= 0) return -1;
    else if (a == 1 && p) return 1;
    else return fastPow(a, p - 2) % p;
}

ulongs gcd(ulongs a, ulongs b)
{
    if (a < b) swap(a, b);
    if (!b) return a;
    else return gcd(b, a % b);
}

ulongs inv[N], sum[N];

void init(int n, int p)
{
    inv[0] = inv[1] = sum[1] = 1;
    for(int i = 2; i <= n; ++ i)
        inv[i] = ((p - p / i) * inv[p % i]) % mod,
        sum[i] = (sum[i - 1] + (inv[i] * inv[i]) % mod) % mod;

}

int main()
{
    ios::sync_with_stdio(false);

    init(N, mod);
    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        auto res = (sum[n] * inv[n]) % mod * 3;
        printf("%llu\n", res % mod);
    }

    return 0;
}