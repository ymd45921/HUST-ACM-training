#include <bits/stdc++.h>

using namespace std;

#define bigint int
bigint read() {
    bigint ret = 0;
    int f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = !f;
    for (; isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - 48;
    return f ? -ret : ret;
}

void write(bigint x) {
    static char str[100];
    if (x < 0) putchar('-'), x = -x;
    int cnt = 0;
    while (x > 9) str[cnt ++] = char((x % 10) + 48), x /= 10;
    str[cnt ++] = char(x + 48);
    while (cnt --) putchar(str[cnt]);
}
#undef bigint
#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))

const int N = 2e5 + 5;

struct fws {
    vector<int> head;
    vector<pair<int, int>> e;
    vector<int> deg;

    explicit fws(int siz) : head(siz, -1), deg(siz) {}

    void renew(int siz) {
        head.resize(siz), deg.resize(siz);
        fill(head.begin(), head.end(), -1);
        fill(deg.begin(), deg.end(), 0);
        e.clear();
    }

    void add_edge(int u, int v) {
        auto tmp = make_pair(v, head[u]);
        head[u] = (int)e.size(), ++ deg[u];
        e.emplace_back(move(tmp));
    }
};

/*
namespace tree_diameter {
    int dis[N];
    fws *pg;

    void clear(int siz) {
        memset(dis, -1, sizeof(int) * siz);
    }

    void dfs(int u) {
        auto &[head, e, deg] = *pg;
        for (auto i = head[u]; i != -1; i = e[u].second)
            if (dis[e[u].first] < 0) {
                dis[e[u].first] = dis[u] + 1;
                dfs(dis[e[u].first]);
            }
    }

    auto dual_dfs(int n) {
        clear(n + 1);
        dis[1] = 0, dfs(1);
        auto st = make_pair(0, 1);
        for (int i = 1; i <= n; ++ i)
            maximize(st, make_pair(dis[i], i));
        clear(n + 1);
        dis[st.second] = 0, dfs(st.second);
        auto ed = make_pair(0, st.second);
        for (int i = 1; i <= n; ++ i)
            maximize(ed, make_pair(dis[i], i));
        return make_pair(st.second, ed.second);
    }
}
*/

class ya_dsu {
    vector<int> fa;

    void join(int u, int v) {
        if (fa[u] > fa[v]) swap(u, v);
        fa[u] += fa[v], fa[v] = u;
    }

public:

    explicit ya_dsu(int n) : fa(n, -1) {}

    void renew(int siz) {
        fa.resize(siz);
        fill(fa.begin(), fa.end(), -1);
    }

    int id(int u) { return fa[u] < 0 ? u : fa[u] = id(fa[u]); }

    bool connect(int u, int v) {
        u = id(u), v = id(v);
        if (u == v) return false;
        else return join(u, v), true;
    }

    int size(int u) { return -fa[id(u)]; }
};

signed main() {
    fws g(0);
    g.head.reserve(N), g.e.reserve(N * 2), g.deg.resize(N);
    vector<int> vis;
    list<int> leaf;
    vis.reserve(N);
    ya_dsu sub(0);
    const auto check = [&](int k) {
        for (auto ii : leaf) {
            if (sub.size(ii) < k)
                return false;
        }
        return true;
    };
    for (auto T = read(); T --;) {
        auto n = read(), k = read();
        g.renew(n + 1), sub.renew(n + 1);
        vis.resize(n + 1), leaf.clear();
        fill(vis.begin(), vis.end(), 0);
        for (int i = 1; i < n; ++ i) {
            int u = read(), v = read();
            g.add_edge(u, v), g.add_edge(v, u);
        }
        if (1 == k) {
            write(n - 1), puts("");
            continue;
        }
        for (int i = 1; i <= n; ++ i)
            if (g.deg[i] == 1) leaf.push_back(i), vis[i] = 1;
        int ans = n - 1, timestamp = 1;
        auto &head = g.head, &deg = g.deg; auto &e = g.e;
        while (ans > 0 && !check(k)) {
            while (!leaf.empty() && vis[leaf.front()] == timestamp) {
                auto u = leaf.front(), v = 0;
                leaf.pop_front();
                if (sub.size(u) >= k) continue;
                for (auto ii = head[u]; ii >= 0; ii = e[ii].second) {
                    if (!vis[e[ii].first] || vis[e[ii].first] == 1 + timestamp) {
                        v = e[ii].first, -- ans, -- deg[v];
                        if (deg[v] == 1) leaf.push_back(v), vis[v] = 1 + timestamp;
                        break;
                    }
                }
                if (!v) { leaf.clear(), ans = 0; break; }
                sub.connect(u, v);
            }
            ++ timestamp;
        }
        write(max(ans, 0)), puts("");
    }
    return 0;
}