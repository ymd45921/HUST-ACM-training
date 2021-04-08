#include <bits/stdc++.h>

using namespace std;
const auto null = nullptr;

const int N = 110;
vector<int> go[N];
int dep[N], nxt[N];
vector<int> ans;

void clear(int n) {
    for (int i = 1; i <= n; ++ i)
        go[i].clear();
    ans.clear();
}

void tagDepth(int u) {
    dep[u] = 1, nxt[u] = 0;
    for (auto v : go[u]) {
        tagDepth(v);
        dep[u] = max(dep[u], dep[v] + 1);
    }
    for (auto v : go[u])
        if (dep[v] == dep[u] - 1)
            nxt[u] = v;
}

void dfsSlave(int u, int &slave) {
    if (slave > 0) {
        -- slave, ans.push_back(u);
        if (1 == dep[u] || !slave) return;
        for (auto v : go[u]) {
            if (!slave) return;
            dfsSlave(v, slave);
            ans.push_back(u);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int T, n, k, u; cin >> T;
    while (T --) {
        cin >> n >> k;
        for (int v = 2; v <= n; ++ v)
            cin >> u, go[u].push_back(v);
        tagDepth(1);
        int master = min(k, dep[1]), slave = max(0, k - dep[1]);
        for (u = 1; u && master; u = nxt[u]) {
            ans.push_back(u), -- master;
            if (slave) {
                for (auto v : go[u]) {
                    if (v != nxt[u]) {
                        if (!slave) break;
                        dfsSlave(v, slave);
                        ans.push_back(u);
                    }
                }
            }
        }
        cout << ans.size() - 1 << endl;
        for (auto ii : ans) cout << ii << ' ';
        cout << endl;
        clear(n);
    }
}