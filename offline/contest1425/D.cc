/**
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>

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
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int N = 2060
;struct clone
{int x, y, val;}
cls[N];
bitset<N> re[N];
int sum[N];
struct cmp
{bool operator()(int i, int j){return sum[i] < sum[j];}};

int dis(clone &a, clone &b)
{return abs(a.x - b.x) + abs(a.y - b.y);}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n = nextInt(), m = nextInt(), r = nextInt();
    for (int i = 1; i <= n; ++ i)
    {
        int x = nextInt(), y = nextInt(), val = nextInt();
        sum[i] = val, cls[i] = {x, y, val}, re[i][i] = true;
    }
    for (int i = 1; i <= n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
        {
            if (dis(cls[i], cls[j]) <= r)
            {
                re[i][j] = re[j][i] = true;
                sum[i] += cls[j].val, sum[j] += cls[i].val;
            }
        }
    set<int, cmp> s;
    for (int i = 1; i <= n; ++ i) s.insert(i);
    longs ans = 0;
    

    return 0;
}

