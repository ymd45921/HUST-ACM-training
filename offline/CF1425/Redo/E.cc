/**
 *
 * 原本以为 k=1 的时候只有两种情况
 * 没想到题解里竟然直接给了 5 种 == 
 * 也难怪过不了；使用宽泛的方法反而覆盖了所有情况
 * 
 * 这个破代码属实恶心，仏了。
 * 
 * 仔细想想，还是没有十分搞清楚答案的五种情况
 * 也许它说的最优是一种更加大局观的层面上的
 * 
 * 有谁能想到我是 k = 2 写错了呢？
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cassert>

using namespace std;
using longs = long long;
using uint = unsigned;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>

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

const int N = 1e5 + 5;
int a[N], d[N], n, m[N];
longs sum[N], suf[N];
#define suf(x) (sum[n] - sum[x - 1])
#define e(i) (a[i] - d[i])

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = 1, k;
    m[0] = 0x7fffffff;
    while (t --)
    {
        n = nextInt(), k = nextInt();
        for (int i = 1; i <= n; ++ i)
            sum[i] = sum[i - 1] + (a[i] = nextInt());
        for (int i = 1; i <= n; ++ i)
            m[i] = min(m[i - 1], (d[i] = nextInt())); 
        suf[n] = max(0ll, suf(n) - d[n]);
        for (int i = n - 1; i; -- i)
            suf[i] = max(max(suf(i) - d[i], 0ll), suf[i + 1]);
        // for (int i = 1; i <= n; ++ i)
            // printf("sum[%d] = %lld, suf(%d) = %lld, m[%d] = %d;\n", i, sum[i], i, suf(i), i, m[i]);    
        if (!k) printf("%lld\n", suf[1]);
        else if (k >= 2)
        {
            int dd = m[n - 1];
            printf("%lld\n", max(sum[n] - dd, (longs)max(e(n), 0)));    // may be not activate any point
        }
        else
        {
            longs ans = max(0ll, suf[2] + max(0, e(1)));
            for (int i = 1; i < n; ++ i)    // a ring and a link
                ans = max(ans, max(sum[i] - m[i], 0ll) + suf[i + 1]);
            for (int i = 2; i < n; ++ i)    // a link skip a point, n can be skipped (like a ring)
                ans = max(ans, max(0ll, sum[n] - d[1] - a[i]) + max(0, e(i)));
            printf("%lld\n", ans);   
        }
    }

    return 0;
}

