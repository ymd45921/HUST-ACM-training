/**
 * 离散并查集
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <unordered_map>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace UFS
{
    unordered_map<int, int> p;
    unordered_map<int, pair<int, int>> cnt;

    void init()
    {
        p.clear();
        cnt.clear();
    }

    int father(int x)
    {
        if (!p.count(x)) p[x] = x, cnt[x] = {1, 0};
        if (p[x] == x) return x;
        auto &fa =  cnt[p[x]], &now = cnt[x];
        fa.first += now.first, fa.second += now.second;
        cnt.erase(x);
        return p[x] = father(p[x]);
    }

    int join(int x, int y)
    {
        auto fx = father(x), fy = father(y);
        if (fx == fy)
        {
            cnt[fx].second += 1;
            return p[fx];
        }
        auto &to = cnt[fy], &from = cnt[fx];
        to.first += from.first, to.second += from.second + 1;
        cnt.erase(fx);
        return p[fx] = p[fy];
    }
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    for (int i = 1; i <= t; ++ i)
    {
        int n = nextInt(), ans = 0;
        UFS::init();
        while (n --)
        {
            int a = nextInt(), b = nextInt();
            UFS::join(a, b);
        }
        for (auto &xx : UFS::cnt)
            ans += min(xx.second.first, xx.second.second);
        printf("Case #%d: %d\n", i, ans);
    }

    return 0;
}