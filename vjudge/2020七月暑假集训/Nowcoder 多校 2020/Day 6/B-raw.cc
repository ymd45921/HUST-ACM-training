/**
 *
 * 缺少了：
 * - 模逆元优化：递推 sum 和 pow2 的逆元
 * - 分数的分母分子可以约分；
 * OEIS，永远的神！
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

ulongs fracMod(ulongs a, ulongs b = 1)
{
    a %= mod, b %= mod;
    return a * inverse(b, mod) % mod;
}

ulongs pow2[N], sum[N], pro[N];
ulongs ans[N], x_sum[N];

void process()
{
    pow2[0] = sum[0] = pro[0] = 1;
    ans[0] = x_sum[0] = 0;
    const int lim = 2e7;
    for (int i = 1; i <= lim; ++ i)
    {
        pow2[i] = (pow2[i - 1] * 2) % mod;
        auto p_1 = (pow2[i] + mod - 1) % mod;
        pro[i] = pro[i - 1] * p_1 % mod;
        sum[i] = sum[i - 1] * pow2[i] % mod;
        auto numerator = sum[i - 1] * pro[i];
        auto denominator = sum[i - 1] * sum[i - 1] % mod * pow2[i];
        ans[i] = fracMod(numerator, denominator);
        x_sum[i] = x_sum[i - 1] ^ ans[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    process();
#ifdef TRICK
    freopen("out.txt", "w", stderr);
    cerr << "[" << endl << "\t";
    for (int i = 0; i <= 1e7; ++ i)
    {
        cerr << x_sum[i] << ", ";
        if (i % 10 == 9) cerr << "\n\t";
    }
    cerr << "\n, 0];" << endl;
#endif
    int t, n;
    cin >> t;
    while (t --)
    {
        cin >> n;
        cout << x_sum[n] << endl;
    }

    return 0;
}