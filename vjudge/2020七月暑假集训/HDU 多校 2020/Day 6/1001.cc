/**
 * 有哪里写错了……
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

#define LOG(x...) fprintf(stderr, x)
#define SUM(l, r) ((sum[r] - sum[(l) - 1] + mod) % mod)

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

void test(int n)
{
    for (int k = 1; k <= n; ++ k)
    {
        for (int i = 1; i <= n; ++ i)
            LOG("%d ", min(min(n - k + 1, k), min(i, n - i + 1)));
        LOG("\n");
        fflush(stderr);
    }
}

const int N = 2e5 + 5;
const longs mod = 1e9 + 7;
longs inv[N], sum[N], w[N], s[N];

void initInverse(int n, longs p)
{
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
    inv[0] = 0;
}

int main()
{
    ios::sync_with_stdio(false);

    initInverse(N, mod);
    for (int i = 1; i <= N; ++ i)
        sum[i] = (sum[i - 1] + inv[i]) % mod;
    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        auto half = (n + 1) % 2;
        for (int i = 1; i <= n; ++ i)
            s[i] = nextInt();
        w[1] = SUM(1, n);
        for (int i = 2; i <= half; ++ i)
            w[i] = ((w[i - 1] + SUM(i, n - i + 1) % mod)) % mod;
        for (int i = n; i > half; -- i)
            w[i] = w[n - i + 1];
        longs ans = 0, all = inv[n] * inv[n + 1] % mod * 2 % mod;
        for (int i = 1; i <= n; ++ i)
            ans += w[i] * s[i] % mod, ans %= mod;
        ans = ans * all % mod;
        printf("%lld\n", ans);
    }

    return 0;
}