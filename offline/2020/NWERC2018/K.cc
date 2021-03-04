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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    string key, b;
    cin >> n >> m >> key >> b;
    string a = b;
    int siz = a.length();
    for (int i = siz - n, j = 0; j < n; ++ i, ++ j)
        a[i] = key[j];
    while (-- siz >= n)
    {
        a[siz - n] = (b[siz] - a[siz] + 260) % 26 + 'a';
    }
    cout << a << endl;
    return 0;
}

