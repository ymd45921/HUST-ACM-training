/**
 *
 * 因为每条边产生的贡献是欧氏距离的平方，所以可以分离二维
 * 这种二位的题目是可以分开解决的，那么我们讨论一维情况下：
 * 
 * 题目的要求在一维情况下：
 * - 构造n个点，每个点都在上一个点的右边；
 * - 每个点都和一个固定的值成边，由边产生贡献；
 * - 
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
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int N = 1e5 + 5;
struct {int s, t;} p[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    using In::read;

    int n = nextInt();
    for (int i = 1; i <= n; ++ i)
        read(p[i].s, p[i].t);
        
    

    return 0;
}

