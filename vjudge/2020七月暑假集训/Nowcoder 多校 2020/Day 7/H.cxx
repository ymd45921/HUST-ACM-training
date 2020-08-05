/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>

#define VAR(var) cerr << ""#var" = " << var << endl

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
auto sum_nDivK$brute(longs n, longs k)
{
    longs _ceil = 0, _floor = 0;
    for (longs i = 1; i <= k; ++ i)
    {
        longs tmp = n / i, xx = n % i ? 1 : 0;
        _floor = (_floor + tmp) % mod;
        _ceil = (_ceil + tmp + xx) % mod;
    }
    return make_pair(_floor, _ceil);
}
#endif

longs sum_nDivK$floor(longs n, longs k)
{
    longs ans = 0, xx = min(n, k);
    while (xx)
    {
        auto div = n / xx;
        auto kk = n / (div + 1);
        ans = (ans + (xx - kk) * div % mod) % mod;
        xx = kk;
    }
    return ans;
}

longs sum_nDivK$ceil(longs n, longs k)
{
    longs ans = max(0ll, k - n + 1), xx = min(n - 1, k);
    while (xx)
    {
        auto div = n / xx + bool(n % xx);
        auto kk = n / div - !bool(n % div);
        ans = (ans + (xx - kk) * div % mod) % mod;
        xx = kk;
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
        const auto _n = mod - n % mod;
        auto _ceil = sum_nDivK$ceil(n, k);
        auto _floor = sum_nDivK$floor(n, k);
#ifdef assert
        auto _brute = sum_nDivK$brute(n, k);
        VAR(_ceil); VAR(_brute.second);
        VAR(_floor); VAR(_brute.first);
        assert(_ceil == _brute.second);
        cerr << "Assertion of ceil success.\n";
        assert(_floor == _brute.first);
        cerr << "Assertion of floor success.\n";
#endif
        auto ans = (_n + _ceil + _floor) % mod;
        cout << ans << endl;
    }

    return 0;
}