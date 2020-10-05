/**
 *
 * 我们仍未听见那天 TLE 的原因
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
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

const int N = 5e5 + 5;
int s[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using In::read;

    int n, c, b, x;
    read(n, c, b);
    vector<int> z;
    memset(s, -1, sizeof s);
    while (b --)
    {
        read(x);
        z.push_back(x);
        s[x] = 0;
    }
    s[1] = c % 2;
    c = c / 2 * 2;
    for (int i = 2; c && i < n; ++ i)
        if (s[i] != -1) continue;
        else if (s[i - 1] == 1) s[i] = 0;
        else if (s[i + 1] != 1) s[i] = 1, c -= 2;
        else s[i] = 1;
    for (int i = 1; i <= n; ++ i)
        putchar(s[i] > 0 ? '1' : '0');
    puts("");

    return 0;
}

