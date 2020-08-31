/**
 *
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

const longs mod = 998244353;
const longs p = mod - 2;

int fracMod(longs a, longs b)   // 费马小定理法
{
    auto n = p;
    longs ans = 1;
    while (n)
    {
        if (n & 1) ans = (ans * b) % mod;
        b = (b * b) % mod;
        n >>= 1;
    }
    ans = (ans * a) % mod;
    return (int) ans;
}

const int N = 1e6 + 5;
longs ans[N];

auto init = []
{
    longs a = 1, b = 1;
    for (longs i = 1; i < N; ++ i)
    {
        a = (a * i) % mod;
        b = (2 * b * (2 * i + 1)) % mod;
        ans[i] = fracMod(a, b);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    init();
    longs n;
    while (cin >> n) cout << ans[n] << endl;

    return 0;
}