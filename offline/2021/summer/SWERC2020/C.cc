#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
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

const int N = 1050;
const double eps = 1e-6;

#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

int compareTo(double x, double y) {
    return fabs(x - y) < eps ? 0 : sgn(x - y);
}

struct ya_dsu {
    vector<int> fa;

    explicit ya_dsu(int n) : fa(n, -1) {}

    void clear() { fill(fa.begin(), fa.end(), -1); }

    int find(int u) { return fa[u] < 0 ? u : fa[u] = find(fa[u]); }

    void join(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (fa[u] > fa[v]) swap(u, v);
        fa[u] += fa[v], fa[v] = u;
    }

    int size(int u) { return -fa[find(u)]; }
};

struct point {
    double x, y;

    point() = default;
    point(double x, double y) : x(x), y(y) {}

    double distance(const point rhs) const {
        auto dx = x - rhs.x, dy = y - rhs.y;
        return sqrt(dx * dx + dy * dy);
    }
} p[N];

bool cross(int i, int j, double r) {
    return compareTo(p[i].distance(p[j]), 2 * r) <= 0;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    int x = read(), y = read(), n = read();
    for (int i = 1; i <= n; ++ i)
        cin >> p[i].x >> p[i].y;
    ya_dsu dsu(n + 5);
    const auto binary = [&](double r) {
        dsu.clear();
        for (int i = 1; i <= n; ++ i) {
            for (int j = i + 1; j <= n; ++ j)
                if (cross(i, j, r)) dsu.join(i, j);
            if(p[i].y - r <= eps) dsu.join(i, n + 1); // xia
            if(p[i].y + r - y >= -eps) dsu.join(i, n + 2); // shang
            if(p[i].x - r <= eps) dsu.join(i, n + 3); // zuo
            if(p[i].x + r - x >= -eps) dsu.join(i, n + 4); // you
        }
        return !(dsu.find(n + 1) == dsu.find(n + 2) || dsu.find(n + 3) == dsu.find(n + 4)
        || dsu.find(n + 3) == dsu.find(n + 1) || dsu.find(n + 2) == dsu.find(n + 4));
    };

    double l = 0, r = max(x, y);
    double ans;
    while(compareTo(l, r) <= 0)
    {
        double mid = (l + r) / 2.;
        if(binary(mid))
        {
            ans = mid;
            l = mid + eps;
        }
        else
        {
            r = mid - eps;
        }
    }
    printf("%.6f\n", l);
    return 0;
}
#pragma clang diagnostic pop