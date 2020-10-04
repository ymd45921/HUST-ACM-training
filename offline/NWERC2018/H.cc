/**
 *
 * TLE 10 到底是个什么几把
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

#define eprintf(x...) fprintf(stderr, x)
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

const int N = 5e5 + 5;
int z[N], s[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, c, b;
    read(n, c, b);
    for (int i = 0; i <= n; ++ i) s[i] = -1;
    for (int i = 1; i <= b; ++ i)
        read(z[i]), s[z[i]] = 0;
    // for (int i = 1; i <= n; ++ i)
    //     cout << (s[i] == -1 ? '?' : '0');
    // cout << endl;    
    int iii = z[1] - 1, bb = 1;
    while (iii && s[iii] == -1)
        s[iii] = bb, bb = 1 - bb, -- iii;
    for (int i = 1; i <= b; ++ i)
    {
        iii = z[i] + 1, bb = 1;
        while (iii <= n && s[iii] == -1)
            s[iii] = bb, bb = 1 - bb, ++ iii;
    }    
    int change = 0, last = s[1], ii = 1;
    for (int i = 1; i <= n; ++ i)
        if (last != s[i]) ++ change, last = s[i];
    // for (int i = 1; i <= n; ++ i)
    //     cout << s[i];
    // cout << ", change = " << change << endl;     
    if ((change - c) % 2) s[1] = 1 - s[1];
    auto d = (change - c) / 2 * 2;
    assert(d % 2 == 0);
    // printf("%d\n", d);
    // for (int i = 1; i <= n; ++ i)
    //     printf("%d", s[i]);
    // printf("\n");    
    ii = 2;
    while (d > 0)
    {
        if (s[ii] == 0) continue;
        if (ii > n) break;
        s[ii] = 0, d -= 2, ++ ii;
    }
    for (int i = 1; i <= n; ++ i)
        printf(s[i] ? "1" : "0");
    puts("");    
    return 0;
}

