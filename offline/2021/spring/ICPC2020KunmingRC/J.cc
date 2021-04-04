#include <iostream>
#include <vector>
#include <tuple>
#include <bitset>
#include <list>

using namespace std;
using longs = long long;

const int N = 1e5 + 5;
int a[N];
bitset<N> vis;

void dfs(vector<int> &arr, int u)
{
    if (u == a[u]) return;
    if (vis[u]) return;
    else
        vis.set(u),
                arr.push_back(u),
                dfs(arr, a[u]);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n; cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i];
    list<vector<int>> circles, sw;
    vector<vector<int>> ans(30);
    vector<int> tmp;
    for (int i = 1; i <= n; ++ i)
        if (!vis.test(i))
            circles.emplace_back(),
                    dfs(circles.back(), i);
    int rounds = 0;
    for (auto &ii : circles)
    {
        int steps = 0;
        while (ii.size() > 1)
        {
            const int siz = ii.size();
            tmp.clear(), ++ steps;
            if (siz == 2)
            {
                ans[steps].push_back(ii[0]),
                ans[steps].push_back(ii[1]);
                break;
            }
            for (int i = 1; i <= siz; i += 2)
                tmp.push_back(ii[i % siz]);
            for (int i = 1; i < siz; i += 2)
                ans[steps].push_back(ii[i]),
                ans[steps].push_back(ii[(i + 1) % siz]);
            swap(tmp, ii);
        }
        rounds = max(rounds, steps);
    }
    cout << rounds << endl;
    for (int i = 1; i <= rounds; ++ i)
    {
        cout << ans[i].size() / 2;
        for (auto ii : ans[i]) cout << ' ' << ii;
        cout << endl;
    }
    return 0;
}