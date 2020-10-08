/**
 *
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define eflush() fflush(stderr)

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? x : -x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}
using In::read;

const int N = 1e5 + 5;
longs p[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n; read(n);
    for (int i = 1; i <= n; ++ i)
        read(p[i]);
    sort(p + 1, p + 1 + n);
    auto me = p[n], a1 = p[n - 1], a2 = p[n - 2];    
    longs ans = a1 - a2 + 2 * (me - a1);
    printf("%lld\n", ans);
    return 0;
}

