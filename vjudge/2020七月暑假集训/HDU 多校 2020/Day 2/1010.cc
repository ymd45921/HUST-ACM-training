/**
 *
 * HDU OJ 不支持 $ 命名
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

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

struct item
{
    int a, b, c, d;

    friend istream &operator >>(istream &is, item &it)
    { return is >> it.a >> it.b >> it.c >> it.d; }

    item operator +(const item &rhs) const
    { return {a + rhs.a, b + rhs.b, c + rhs.c, d + rhs.d}; }
};

vector<item> vec[55];

longs $ans = 0;

longs dfs(int tp, item xx)
{
    if (!tp)
    {
        longs ans = (100 + xx.a) * (100 + xx.b) * (100 + xx.c) * (100 + xx.d);
        return $ans = max(ans, $ans);
    }
    for (auto & ii : vec[tp])
        dfs(tp - 1, xx + ii);
    dfs(tp - 1, xx);
    return $ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, k;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        for (int i = 1; i <= k; ++ i)
            vec[i].clear();
        for (int i = 0; i < n; ++ i)
        {
            int tp; cin >> tp;
            vec[tp].emplace_back();
            cin >> vec[tp].back();
        }
        auto ans = dfs(k, {0, 0, 0, 0});
        cout << ans << endl;
    }

    return 0;
}
