#ifndef CLION_DEBUG
#pragma GCC optimize(3, "Ofast", "inline")
#endif
#include <bits/stdc++.h>

using namespace std;
using llong = long long;
using lll = __int128;

#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

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
    while (x > 9) {
        str[cnt ++] = char(x % 10 + 48);
        x /= 10;
    }
    str[cnt ++] = char(x + 48);
    while (cnt --) putchar(str[cnt]);
}
#undef bigint

struct fws {
    using edge = pair<int, int>;
    vector<int> head, cnt;
    vector<edge> e;

    void renew(int siz) {
        head.resize(siz), cnt.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
        fill(cnt.begin(), cnt.end(), 0);
    }

    void renew(int siz, int res) {
        renew(siz), e.reserve(res);
    }

    void add_edge(int u, int v) {
        edge tmp(v, head[u]);
        head[u] = (int) e.size();
        e.emplace_back(move(tmp));
        ++ cnt[u];
    }
} g;

const int N = 1e5 + 5;
vector<pair<int, int>> lim;
llong f[N][2];

void dfs(int u, int fa) {
    if (fa && g.cnt[u] == 1) {
        f[u][0] = f[u][1] = 0;
        return;
    }
    auto [lu, ru] = lim[u];
    for (auto i = g.head[u]; ~i;
        i = g.e[i].second) {
        auto v = g.e[i].first;
        if (v == fa) continue;
        dfs(v, u);
        auto [lv, rv] = lim[v];
        f[u][1] += max(f[v][0] + abs(lv - ru), f[v][1] + abs(rv - ru));
        f[u][0] += max(f[v][0] + abs(lv - lu), f[v][1] + abs(rv - lu));
    }
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    lim.reserve(N);
    g.e.reserve(N * 2);
    g.head.reserve(N);
    for (int T = read(); T--;) {
        int n = read();
        for (int i = 1; i <= n; ++ i)
            f[i][0] = f[i][1] = 0;
        lim.resize(n + 1);
        for (int i = 1; i <= n; ++ i) {
            int l = read(), r = read();
            lim[i] = make_pair(l, r);
        }
        g.renew(n + 1);
        for (int i = 1; i < n; ++ i) {
            int u = read(), v = read();
            g.add_edge(u, v), g.add_edge(v, u);
        }
        dfs(1, 0);
        cout << max(f[1][0], f[1][1]) << endl;
    }
    return 0;
}