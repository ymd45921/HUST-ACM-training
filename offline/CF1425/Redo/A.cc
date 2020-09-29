/**
 *
 * 在博弈论中考虑奇偶性的时候考虑 2 和 4 似乎是挺常见的
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

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
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

longs solve(longs n)
{
    if (n & 1) return 1;
    else if (n == 4) return 2;
    else if (n % 4 == 0) return 1;
    else return n / 2;
}

longs go(longs n)
{
    longs ans = 0;
    bool my = true;
    while (n)
    {
        auto now = solve(n);
        if (my) ans += now;
        n -= now, my = !my;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = nextInt();
    while (t --)
    {
        auto n = nextLongs();
        auto ans = go(n);
        printf("%lld\n", ans);
    }

    return 0;
}

