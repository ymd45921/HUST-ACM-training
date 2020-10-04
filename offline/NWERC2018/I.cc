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

const int N = 2e5 + 5;
int c[N];

int main()
{
    // ios::sync_with_stdio(false);
    // std::cin.tie(nullptr);
    // std::cout.tie(nullptr);

    int n; read(n);
    for (int i = 1; i <= n; ++ i)
        read(c[i]);
    sort(c + 1, c + 1 + n);
    bool ok = true;
    double f = 1;
    for (int i = 1; i <= n; ++ i)
        if (c[i] > i) ok = false;    
        else f = min(f, (double)c[i] / i);
    cout << fixed;    
    if (ok) cout << f << endl;
    else puts("-1");    
    return 0;
}

