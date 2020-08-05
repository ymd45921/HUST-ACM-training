/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 55;
bool g[N][N];
int n, m, d[N];

namespace HungaryMatch
{
    int match[2][N];
    int res[N];
    bool vis[N];

    auto unVis = []{memset(vis, 0, sizeof(vis));};

    auto index = [](int i, int j) -> int
    {
        if (match[0][i] == j) return 0;
        else return 1;
    };

    void init()
    {
        memset(match, 0, sizeof(match));
        memcpy(res, d, sizeof(d));
        memset(vis, 0, sizeof(vis));
    }

    bool nextMatch(int i, int x)
    {
        for (int j = 1; j <= n; ++ j)
            if (g[i][j] && !vis[j] &&
                match[0][i] != j && match[1][i] != j)
            {
                vis[j] = true;
                if (!match[0][j] ||
                    nextMatch(match[0][j], index(match[0][j], j)))
                {
                    match[0][j] = i;
                    match[x][i] = j;
                    return true;
                }
                else if (d[j] == 2 && (
                        !match[1][j] ||
                        nextMatch(match[1][j], index(match[1][j], j))))
                {
                    match[1][j] = i;
                    match[x][i] = j;
                    return true;
                }
            }
        return false;
    }

    int maxMatch()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++ i)
        {
            unVis();
            if (nextMatch(i, 0))
                if (d[i] == 2)
                    if (nextMatch(i, 1)) ++ ans; else;
                else ++ ans;
            else continue;
        }
        return ans;
    }

    int count()
    {
        int ans = 0;
        for (int i = 1; i <= n; ++ i)
            if (d[i] == 1) ans += match[0][i] != 0;
            else if (match[0][i] && match[1][i]) ++ ans;
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while (cin >> n >> m)
    {
        for (int i = 0; i <= n; ++ i)
            for (int j = 0; j <= n; ++ j) g[i][j] = false;
        for (int i = 1; i <= n; ++ i) cin >> d[i];
        int mm = m, a, b;
        while (mm --)
        {
            cin >> a >> b;
            g[a][b] = g[b][a] = true;
        }
        HungaryMatch::init();
        HungaryMatch::maxMatch();
        auto x = HungaryMatch::count();
        cerr << "Max matched node is " << x << ".\n";
        cout << (x == n ? "Yes" : "No") << endl;
    }

    return 0;
}