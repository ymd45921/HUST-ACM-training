/**
 *
 * 读了个假题，吐了（
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

const int N = 1050;
vector<int> g[N];

void addEdge(int u, int v, int w)
{
    g[u].push_back(w);
    g[v].push_back(w);
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using In::read;

    int n, u, v, w, m;
    read(n), m = n * (n - 1);
    while (m --)
    {
        read(u, v, w);
        addEdge(u, v, w);
    }
    longs ans = 0;
    for (int i = 1; i <= n; ++ i)
    {
        sort(g[i].begin(), g[i].end());
        auto siz = g[i].size();
        for (int j = 1; j < siz; ++ j)
            ans += max(g[i][j], g[i][j - 1]);
    }
    printf("%lld\n", ans);
    return 0;
}

