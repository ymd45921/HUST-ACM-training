/**
 *
 * 为什么可以这样？这一定又是某种常识吧（
 * 不行，果然不懂==
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
int a[N], b[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        In::read(a[i]);
    for (int i = 1; i <= n; ++ i)
        In::read(b[i]);
    int ans = 0;
    for (int i = 1; i <= n; ++ i)
    {
        int tmp = 0x3f3f3f3f;
        for (int j = 1; j <= n; ++ j)
            tmp = min(tmp, abs(a[i] - b[j]));
        ans = max(ans, tmp);    
    }    
    printf("%d\n", ans);

    return 0;
}

