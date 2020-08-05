/**
 *
 * 实际上最多就两种情况，靠恁娘
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>
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

const int N = 2e5 + 5;
int a[N];
bitset<N> s;
vector<pair<int, int>> ans;

auto bucketCheck = [](int l, int r)
{
    s.reset();
    for (int i = l; i < r; ++ i) s[a[i]] = true;
    const auto cnt = r - l;
    for (int i = 1; i <= cnt; ++ i)
        if (!s[i]) return false;
    return true;
};

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, x;
    cin >> t;
    while (t --)
    {
        cin >> n;
        x = 0;
        for (int i = 0; i < n; ++ i)
            cin >> a[i], x = max(x, a[i]);
        int y = n - x;
        if (bucketCheck(0, x) && bucketCheck(x, n)) ans.emplace_back(x, y);
        if (x != y)
            if (bucketCheck(0, y) && bucketCheck(y, n)) ans.emplace_back(y, x);
        cout << ans.size() << endl;
        for (auto & ii : ans)
            cout << ii.first << ' ' << ii.second << endl;
        ans.clear();
    }

    return 0;
}