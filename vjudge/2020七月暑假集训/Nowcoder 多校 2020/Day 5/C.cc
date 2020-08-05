/**
 *
 * 不是算最大的，是算所有可能的解的和
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int mod = 998244353;

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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, m, k;
    cin >> t;
    while (t --)
    {
        cin >> n >> m >> k;
        auto nn = n / k, mm = n / k;
        auto nnn = n % k, mmm = m % k;
        auto c = min(nnn, mmm), b = abs(mmm - nnn), a = min(nn, mm);
        auto p = fastPow(min(nn, mm), a);
        p = p * fastPow(min(nn + 1, mm + 1), c) % mod;
        if (mmm > nnn) p = p * fastPow(min(nn, mm + 1), b) % mod;
        else p = p * fastPow(min(nn + 1, mm), b) % mod;
        cout << p << endl;
    }

    return 0;
}