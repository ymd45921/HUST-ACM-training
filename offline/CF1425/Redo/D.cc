/**
 *
 * 并不算是很难的题目，但是要有耐心划分
 * 说起谁能杀我，还真的不能直接统计
 * 
 * 写代码存在问题：换一种写法总会有历史遗留问题
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <cassert>

using namespace std;
using longs = long long;
using uint = unsigned;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>
#define eprintf(x) fprintf(stderr, x)
#define var(x) ""#x" = " << x 

template<class T>
inline T nexT()
{
    T x = 0; int f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int N = 1050, mod = 1e9 + 7;
struct snake {int x, y, b;} p[N];
bitset<N> g[N];
int w[N][N], x[N];

int dis(int i, int j)
{return max(abs(p[i].x - p[j].x), abs(p[i].y - p[j].y));}

namespace FastC
{
    const longs mod = ::mod;
    const int N = ::N * 2;
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

    void init(int p = N - 1)
    {
        fact[0] = inv[0] = 1;
        for (int i = 1; i <= p; i++)
            fact[i] = fact[i - 1] * i % mod;
        inv[p] = fastPow(fact[p], mod - 2);
        for (int i = p - 1; i >= 0; i--)
            inv[i] = inv[i + 1] * (i + 1) % mod;
    }

    longs $C(longs n, longs m)
    {
        if (m > n || m < 0) return 0;
        return fact[n] * inv[m] % mod * inv[n - m] % mod;
    }
}

int getW(int x1, int y1, int x2, int y2)
{
    x1 = max(x1, 1), x2 = min(1000, x2);
    y1 = max(y1, 1), y2 = min(1000, y2);
    if (x1 > x2 || y1 > y2) return 0;
    -- x1, -- y1;
    return w[x2][y2] + w[x1][y1] - w[x1][y2] - w[x2][y1];
}

#define square(x, y) (x - r), (y - r), (x + r), (y + r)  

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using FastC::$C;

    int n = nextInt(), m = nextInt(), r = nextInt();
    FastC::init();
    for (int i = 1; i <= n; ++ i)
    {
        p[i] = {nextInt(), nextInt(), nextInt()};
        assert(!g[p[i].x][p[i].y]);
        g[p[i].x][p[i].y] = true;
    }
    for (int i = 1; i < N; ++ i)
        for (int j = 1; j < N; ++ j)
            w[i][j] += w[i - 1][j] + w[i][j - 1] - w[i - 1][j - 1] + g[i][j];
    for (int i = 1; i <= n; ++ i)
        x[i] = getW(square(p[i].x, p[i].y));        
#if 0
    for (int i = 1; i <= 5; ++ i)
    {
        for (int j = 1; j <= 5; ++ j)
            printf("%c ", g[i][j] ? '*' : '.');   
        puts("");    
    }
    for (int i = 1; i <= 5; ++ i)
    {
        for (int j = 1; j <= 5; ++ j)
            printf("%d ", w[i][j]);  
        puts("");    
    }
    for (int i = 1; i <= n; ++ i)
        printf("%d ", x[i]);
    puts("");    
#endif            
    longs ans = 0;        
    for (int i = 1; i <= n; ++ i)
        for (int j = i; j <= n; ++ j)
        {
            int uu = max(p[i].x, p[j].x) - r,
                dd = min(p[i].x, p[j].x) + r,
                ll = max(p[i].y, p[j].y) - r,
                rr = min(p[i].y, p[j].y) + r;
            auto ww = getW(uu, ll, dd, rr), nn = n - ww;
            longs cnt = $C(n, m) - $C(n - ww, m);
            auto u = x[i] - ww, v = x[j] - ww;
            cnt += $C(nn, m) - $C(nn - u, m) - $C(nn - v, m) + $C(nn - v - u, m);
            while (cnt < 0) cnt += mod;
            cnt = cnt * (i == j ? 1 : 2) % mod;
            ans = (ans + cnt * p[i].b % mod * p[j].b % mod);
        }        
    printf("%lld\n", ans);

    return 0;
}

