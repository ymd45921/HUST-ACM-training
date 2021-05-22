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
#undef bigint

const int N = 100050;
int dis[N];

template <class T>
void build_kmp(const T *arr, int *kmp, int len) {
    int i = 0, j = kmp[0] = -1;
    while (i < len)
        if (-1 == j || arr[i] == arr[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

struct fws {
    using edge = tuple<int, int, int>;
    vector<int> head;
    vector<edge> e;

    void renew(int siz, int res = N) {
        head.resize(siz), e.clear();
        fill(head.begin(), head.end(), -1);
    }

    void add_edge(int u, int v, int w) {
        edge tmp(v, w, head[u]);
        head[u] = (int) e.size();
        e.emplace_back(move(tmp));
    }

    using node = pair<int, int>;
    using heap = priority_queue<node, vector<node>, greater<>>;

    void dijkstra(int s, int *d) const {
        fill(d, d + head.size(), 1e9 + 7);
        heap pq(greater<>(), {{d[s] = 0, s}});
        while (!pq.empty()) {
            auto [du, u] = pq.top(); pq.pop();
            if (du > d[u]) continue;
            for (int i = head[u]; ~i; i = get<2>(e[i])) {
                auto [v, w, _] = e[i];
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    pq.emplace(d[v], v);
                }
            }
        }
    }
};

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    int n = read(), m = read(), L = read(), U = read();
    fws g;
    g.renew(n + 1), g.e.reserve(m * 2 + 5);
    while (m --) {
        int i = read(), j = read(), l = read();
        g.add_edge(i, j, l), g.add_edge(j, i, l);
    }
    g.dijkstra(0, dis);
    int ans = 0;
    for (int u = 0; u < n; ++ u)
        for (int i = g.head[u]; ~i;
            i = get<2>(g.e[i])) {
            auto [v, w, _] = g.e[i];
            if (min(dis[u], dis[v]) * 2 < U) ++ ans;
        }

    cout << (ans /= 2) << endl;
}