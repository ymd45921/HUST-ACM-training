#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-transparent-functors"
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>

using namespace std;
using llong = long long;

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
#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))

const int N = 1e5 + 5, M = 1e6 + 5;
const llong inf = 0x3f3f3f3f3f3f3f3fll;
llong a[N + M], b[N + M], sh[N];

struct fws {

    using edge = tuple<int, llong, int>;
    vector<int> head;
    vector<edge> e;

    void renew(size_t siz) {
        head.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
    }

    void add_edge(int u, int v, llong w) {
        edge tmp(v, w, head[u]);
        head[u] = e.size();
        e.emplace_back(move(tmp));
    }
};

bitset<N + M> vis;
using node = pair<llong, int>;
using heap = priority_queue<node, vector<node>, greater<node>>;
heap q;

void dijkstra(const fws &g, int st, llong *dis) {
    while (!q.empty()) q.pop();
    dis[st] = 0, q.emplace(0, st);
    while (!q.empty()) {
        auto u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        else vis[u] = true;
        for (auto i = g.head[u]; i >= 0; i = get<2>(g.e[i])) {
            auto v = get<0>(g.e[i]);
            auto w = get<1>(g.e[i]);
            if (dis[u] + w >= dis[v]) continue;
            dis[v] = dis[u] + w;
            q.emplace(dis[v], v);
        }
    }
}

signed main() {
    fws g;
    g.head.reserve(N + M), g.e.reserve(M * 2);
    vector<int> ans;
    ans.reserve(N);
    for (int T = read(), tc = 1; tc <= T; ++ tc) {
        printf("Case #%d: ", tc);
        int n = read(), m = read();
        g.renew(n + m + 1);
        for (int i = 1; i <= m; ++ i) {
            int t = read(), s = read();
            int v = n + i;
            while (s --) {
                int u = read();
                g.add_edge(u, v, t);
                g.add_edge(v, u, t);
            }
        }
        const auto siz = (n + m + 1) * sizeof(llong);
        memset(a, 0x3f, siz), memset(b, 0x3f, siz);
        vis.reset(), dijkstra(g, 1, a);
        vis.reset(), dijkstra(g, n, b);
        for (int i = 1; i <= n; ++ i)
            sh[i] = max(a[i], b[i]);
        auto sho = *min_element(sh + 1, sh + 1 + n);
        for (int i = 1; i <= n; ++ i)
            if (sh[i] == sho) ans.push_back(i);
        if (sho >= inf) puts("Evil John");
        else {
            printf("%lld\n", sho / 2);
            // for (auto ii : ans)
            //     printf("%d ", ii);
            for(int i = 0; i < ans.size() - 1; ++i)
                printf("%d ", ans[i]);
            printf("%d\n", ans.back());
        }
        ans.clear();
    }
    return 0;
}
#pragma clang diagnostic pop