/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

constexpr ulongs mod = 1e9 + 9;

ulongs fastPow(ulongs a, ulongs b)
{
    longs ans = 1;
    while(b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

ulongs solution(ulongs n, ulongs c, ulongs k)
{
    ulongs mat[2][2] = {{1, 0}, {0, 1}},
            xx[2][2] = {{1, 1}, {1, 0}},
            ii[2][2], nc[2][2];
    const static auto matPow = [&](ulongs n)
    {
        while (n)
        {
            if (n & 1u)
            {
                memset(ii, 0, sizeof ii);
                for (int i = 0; i < 2; ++ i)
                    for (int j = 0; j < 2; ++ j)
                        for (int k = 0; k < 2; ++ k)
                            ii[i][j] += mat[i][k] * xx[k][j],
                                    ii[i][j] %= mod;
                memcpy(mat, ii, sizeof ii);
            }
            memset(ii, 0, sizeof ii);
            for (int i = 0; i < 2; ++ i)
                for (int j = 0; j < 2; ++ j)
                    for (int k = 0; k < 2; ++ k)
                        ii[i][j] += xx[i][k] * xx[k][j],
                                ii[i][j] %= mod;
            memcpy(xx, ii, sizeof ii);
            n >>= 1u;
        }
    };
    const static auto fib = [&]{return mat[1][0] % mod;};
    matPow(c);
    memcpy(nc, mat, sizeof nc);
    ulongs ans = fastPow(fib(), k);
    while (-- n)
    {
        memset(ii, 0, sizeof ii);
        for (int i = 0; i < 2; ++ i)
            for (int j = 0; j < 2; ++ j)
                for (int l = 0; l < 2; ++ l)
                    ii[i][j] += mat[i][l] * nc[l][j],
                            ii[i][j] %= mod;
        memcpy(mat, ii, sizeof ii);
        ans += fastPow(fib(), k), ans %= mod;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, c, k, t;
    cin >> t;
    while (t --)
    {
        cin >> n >> c >> k;
        auto ans = solution(n, c, k) % mod;
        cout << ans << endl;
    }

    return 0;
}