/**
 * 
 * OEIS，永远的神！
 * 和张旭一人优化了一个 log，变成线性时间了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using ulongs = unsigned long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

constexpr int N = 2e7 + 5;
constexpr ulongs mod = 1e9 + 7;

ulongs pow2[N], inv[N];
ulongs x_sum[N];

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

void process()
{
    auto pro = pow2[0] = inv[0] = 1;
    x_sum[0] = 0;
    inv[1] = inverse(2, mod);
    auto sum_1 = inverse(1, mod);
    const int lim = 2e7;
    for (int i = 1; i <= lim; ++ i)
    {
        pow2[i] = (pow2[i - 1] * 2) % mod;
        inv[i] = inv[i - 1] * inv[1] % mod;
        auto p_1 = (pow2[i] + mod - 1) % mod;
        pro = pro * p_1 % mod;
        auto ans = pro * sum_1 % mod * inv[i] % mod;
        sum_1 = sum_1 * inv[i] % mod;
        x_sum[i] = x_sum[i - 1] ^ ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    process();
    int t, n;
    cin >> t;
    while (t --)
    {
        cin >> n;
        cout << x_sum[n] << endl;
    }

    return 0;
}