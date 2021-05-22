/**
 *
 * 给定了一些方块，它们按照某种形式堆的高高；现在你可以向左/右推拉它们：
 * 水平方向上空间无限；要求最后所有的方块都在地上，求这样需要推拉的最少次数
 *
 * 这些卵人代码为什么写的都这么简单（）
 */
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

const int N = 2e5 + 5;
llong a[N], dis[N];

template <class T = llong>
struct fws {
    using edge = tuple<int, T, int>;
    vector<int> head;
    vector<edge> e;

    explicit fws(int n) : head(n, -1), e() {}

    void renew(size_t siz) {
        head.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
    }

    void add_edge(int u, int v, T w) {
        edge tmp(v, w, head[u]);
        head[u] = (int) e.size();
        e.emplace_back(move(tmp));
    }

    using node = pair<T, int>;
    using heap = priority_queue<node, vector<node>, greater<>>;

    void dijkstra(int s, T *d) const {
        fill(d, d + head.size(), numeric_limits<T>());
        d[s] = 0;
        heap pq(greater<>(), {{0, s}});
        while (!pq.empty()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du > d[u]) continue;
            for (int i = head[u]; i >= 0; i = get<2>(e[i])) {
                auto [v, w, _] = e[i];
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.template emplace(d[v], v);
                }
            }
        }
    }
};

signed main() {
    int n = read();
    for (int i = 1; i <= n; ++ i) a[i] = read();
    fws<llong> g(2 * n + 2);
    g.e.reserve(n * 10 + 5);
    const int S = 0, T = 2 * n + 1;

#define in(x) ((x) + n)
#define out(x) ((x))

    g.add_edge(S, in(1), 0);
    g.add_edge(out(n), T, 0);
    for (int i = 1; i <= n; ++ i)
        g.add_edge(in(i), out(i), 2 * max(0ll, a[i] - 1));
    for (int i = 1; i < n; ++ i)
        g.add_edge(out(i), in(i + 1), 0);

    for (llong sum = 0, i = 1; i <= n; ++ i) {
        sum += a[i];
        g.add_edge(S, out(i), max(0ll, sum - 1));
    }
    for (llong sum = 0, i = n; i >= 1; -- i) {
        sum += a[i];
        g.add_edge(in(i), T, max(0ll, sum - 1));
    }

    vector<vector<int>> ll(n + 1), rr(n + 1);
    stack<pair<int, int>> s;
    for (int i = 1; i <= n; ++ i)
        if (a[i] > 1) s.emplace(1, i);
        else if (!a[i] && !s.empty()) {
            auto &[val, id] = s.top();
            rr[id].push_back(i);
            if (++ val == a[id]) s.pop();
        }
    while (!s.empty()) s.pop();
    for (int i = n; i >= 1; -- i)
        if (a[i] > 1) s.emplace(1, i);
        else if (!a[i] && !s.empty()) {
            auto &[val, id] = s.top();
            ll[id].push_back(i);
            if (++ val == a[id]) s.pop();
        }
    vector<pair<int, int>> vn;
    for (int i = 1; i <= n; ++ i) {
        if (a[i] <= 1) continue;
        vn.clear();
        vn.emplace_back(0, in(i));
        auto lls = ll[i].size(), rrs = rr[i].size();
        
    }

    cout << (g.dijkstra(S, dis), dis[T]) << endl;
    return 0;
}