/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cassert>

#define TEST

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const longs mod = 1e9 + 7;

#ifdef assert
longs bruteSolution(longs n, longs k)
{
    longs ans = n % mod;
    auto logN = log(n);
    for (longs kk = 2; kk <= k; ++ kk)
    {
        longs tmp = ((n - 1) / kk + 1) % mod, div = 0;
        if (kk < n) div = longs(logN / log(kk)) % mod;
        else if (kk == n) div = 1;
        ans = (ans + tmp + div) % mod;
    }
    return ans;
}

longs countDirectly(longs n, longs k)
{
    longs ans = n % mod;
    for (longs kk = 2; kk <= k; ++ kk)
    {
        longs tmp = ((n - 1) / kk + 1) % mod;
        auto pp = k;
        while (pp <= n)
        {
            assert((pp - 1) % kk == 0);
            ++ tmp;
            if (n / pp >= k) pp *= k;
            else break;
        }
    }
    return ans;
}

longs bruteSumNDivK(longs n, longs k)
{
    longs ans = 0, kk = min(n, k);
    for (int i = 1; i <= kk; ++ i)
        ans = (ans + n / i) % mod;
    return ans;
}

longs bruteSumLog_kN(longs n, longs k)
{
    longs ans = 0, kk = min(n, k);
    const auto logN = log(n);
    for (int i = 2; i <= kk; ++ i)
    {
        auto logK = log(i);
        longs div = logN / logK;
        ans = (ans + div) % mod;
    }
    return ans;
}
#endif

longs sumNDivK(longs n, longs k)
{
    longs ans = 0;
    while (k)
    {
        auto div = n / k;
        auto kk = n / (div + 1);
        ans = (ans + (k - kk) * div % mod) % mod;
        k = kk;
    }
    return ans;
}

longs sumLog_kN(longs n, longs k)
{
    longs ans = 0, kk = min(n, k);
    const auto logN = log(n);
    while (kk > 1)
    {
        auto logK = log(kk);
        longs div = logN / logK;
        longs nxt = pow(n, 1.0 / (div + 1.0));
        ans = (ans + (kk - nxt) * div % mod) % mod;
        kk = nxt;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, k;
    while (cin >> n >> k)
    {
        auto ans = (sumNDivK(n - 1, k) + k + sumLog_kN(n, k)) % mod;
        cout << ans << endl;
#ifdef TEST
        cerr << "TEST(" << n << ", " << k << "):\n";
        assert(sumNDivK(n - 1, k) == bruteSumNDivK(n - 1, k));
        cerr << "Assertion of (n - 1) / k sum has passed.\n";
        assert(sumLog_kN(n, k) == bruteSumLog_kN(n, k));
        cerr << "Assertion of log_k(n) sum has passed.\n";
#elif defined assert
        auto brute = bruteSolution(n, k);
        cerr << brute << endl;
        assert(ans == brute);
#endif
    }

    return 0;
}