/**
 *
 * 原以为还要求交集什么的，但是发现直接扫一遍贪心就行了
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>
#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

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

const int N = 2e5 + 5;
int a[N]; longs sum[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        sum[i] = (a[i] = nextInt()) + sum[i - 1];
    set<longs> s;
    s.insert(0);
    int ans = 0;
    longs pre = 0;
    for (int i = 1; i <= n; ++ i)
    {
        if (s.count(sum[i] - pre))  
        {
            s.clear();
            pre = sum[i - 1];
            ++ ans;
            s.insert(0);
        }
        s.insert(sum[i] - pre);
    }
    printf("%d\n", ans);
    return 0;
}

