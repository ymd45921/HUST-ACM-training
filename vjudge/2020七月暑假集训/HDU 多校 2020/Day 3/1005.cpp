/**
 *
 * 出锅：
 * - 都这么大人了还被 long long 卡
 * - 快读板子出锅，以后请使用这里的新板子
 * 这个题目调试到比赛结束（
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <cstring>

#define CODE 2
#define READ 1
#define ALL 3

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

const int N = 1e5 + 5;
const longs mod = 1e9 + 7;
int ch[N], tp[4];
struct {longs r, c, contrib;} hook[N];

namespace FastC
{
    const longs mod = 1e9 + 7;
    longs fact[N], inv[N];

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

    void init(int p)
    {
        fact[0] = 1;
        for (int i = 1; i <= p; i++)
            fact[i] = fact[i - 1] * i % mod;
        inv[p] = fastPow(fact[p], mod - 2);
        for (int i = p - 1; i >= 0; i--)
            inv[i] = inv[i + 1] * (i + 1) % mod;
    }

    longs C(longs n, longs m)
    {
        if (m > n) return 0;
        return fact[n] * inv[m] % mod * inv[n - m] % mod;
    }
}

namespace UFS
{
    using number = int;
    number p[N];

    void init(int n = N)
    {
        for (int i = 0; i < n; ++ i)
            p[i] = i;
    }

    number father(int x)
    {
        return p[x] == x ? x : p[x] = father(p[x]);
    }

    number join(int x, int y)
    {
        return p[father(x)] = p[father(y)];
    }
}

longs calculate(longs cc, longs rr, longs xc, longs xr)
{
    using FastC::C;
    auto _3 = C(cc, 3) + C(cc, 2) * rr % mod;
    auto _2 = C(cc, 2) * (xc + xr) % mod + cc * rr % mod * xc % mod;
    return (_3 + _2) % mod;
}

longs calculate(longs cc, longs rr)
{return calculate(cc, rr, tp[CODE] - cc, tp[READ] - rr);}

longs connect(longs old, int u, int v)
{
    auto ufa = UFS::father(u), vfa = UFS::father(v);
    if (ufa == vfa) return old;
    auto tmp = (old + hook[ufa].contrib + hook[vfa].contrib) % mod;
    auto nr = hook[ufa].r + hook[vfa].r, nc = hook[ufa].c + hook[vfa].c;
    auto fa = UFS::join(u, v);
    hook[fa] = {nr, nc, calculate(nc, nr)};
    return (tmp - hook[fa].contrib + mod) % mod;
}

int main()
{
    FastC::init(1e5 + 1);
    int t = nextInt(), n;
    while (t --)
    {
        n = nextInt();
        memset(ch, 0, sizeof(int) * (n + 1));
        UFS::init(n + 1);
        tp[CODE] = tp[READ] = tp[ALL] = 0;
        for (int i = 1; i <= n; ++ i)
        {
            ++ tp[ch[i] = nextInt()];
            if (ch[i] == CODE) hook[i] = {0, 1, 0};
            else hook[i] = {1, 0, 0};
        }
        longs all = calculate(tp[CODE], tp[READ]);
        cout << all << endl;
        auto tmp = all;
        for (int i = 1; i < n; ++ i)
        {
            int u = nextInt(), v = nextInt();
            tmp = connect(tmp, u, v);
            cout << tmp << endl;
        }
    }

    return 0;
}