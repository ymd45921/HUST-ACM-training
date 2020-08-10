/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <unordered_map>

#define F(x) (xx[common[x]])
#define G(x) (yy[common[x]])

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

const ulongs mod = 998244353;

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

template <int n> vector<int> &EulerSieve()
{
    static vector<int> prime;
    bitset<n> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime.push_back(i);
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = true;
            if (i % pp == 0) break;
        }
    }
    return prime;
}

int main()
{
    ios::sync_with_stdio(false);

    const int N = 1e5 + 5;
    const auto &prime = EulerSieve<N>();
    int a = nextInt(), b = nextInt(), c = nextInt();
    int d = nextInt(), x = nextInt(), y = nextInt();
    unordered_map<int, uint> xx, yy;
    vector<int> common;
    for (auto &p : prime)
    {
        if (x % p == 0)
        {
            uint pp = p * 2, ii = 2;
            while (x % pp == 0) pp <<= 1u, ii <<= 1u;
            pp >>= 1u, ii >>= 1u;
            while (pp)
            {
                if (x % pp == 0) xx[p] |= ii;
                pp >>= 1u, ii >>= 1u;
            }
        }
        if (y % p)
        {
            uint pp = p * 2, ii = 2;
            while (y % pp == 0) pp <<= 1u, ii <<= 1u;
            pp >>= 1u, ii >>= 1u;
            while (pp)
            {
                if (y % pp == 0) yy[p] |= ii;
                pp >>= 1u, ii >>= 1u;
            }
        }
    }
    auto jj = xx.begin(), je = xx.end();
    for (auto &ii : xx)
    {
        while (jj != je && jj->first < ii.first) ++ jj;
        if (jj == je) break;
        else if (jj->first == ii.first) common.push_back(ii.first);
    }
    longs ans = 1;
    auto k = common.size();
    for (int i = 0; i < k; ++ i)
    {
        longs sum = 0;
        for (auto j = c; j <= d; ++ j)
        {
            auto ll = j * G(i) / F(i);
            
        }
    }


    return 0;
}