/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
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

const int N = 1e6 + 5;
vector<pair<int, int>> a;
int sec[N], cnt = 0;

auto join = [](int ii){if (!sec[a[ii].second]) ++ cnt; ++ sec[a[ii].second];};
auto part = [](int ii){-- sec[a[ii].second]; if (!sec[a[ii].second]) -- cnt;};

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt(), m = nextInt();
    for (int i = 1; i <= n; ++ i)
    {
        int k = nextInt();
        while (k --)
        {
            int x = nextInt();
            a.emplace_back(x, i);
        }
    }
    if (m == 1) {printf("0\n"); return 0;}
    sort(a.begin(), a.end());
    int l = 0, r = 0, siz = a.size(), ans = 0x7fffffff;
    while (r < siz)
    {
        while (r < siz && cnt < m) join(r ++);
        while (l < r && cnt == m) part(l ++);
        ans = min(ans, a[r - 1].first - a[l - 1].first);
    }
    printf("%d\n", ans);

    return 0;
}