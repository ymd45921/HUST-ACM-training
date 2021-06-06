#include <bits/stdc++.h>

using namespace std;
using llong = long long;
using ldouble = long double;

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

const int N = 1e5 + 5;
int x[N], v[N], l[N], r[N];
bitset<N> dead;

ldouble solve(int i, int j) {
    if (v[i] == v[j]) return -1;
    ldouble dx = x[j] - x[i], dv = v[i] - v[j];
    return dx / dv;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    int n = read();
    for (int i = 1; i <= n; ++ i)
        x[i] = read(), v[i] = read();
    for (int i = 2; i < n; ++ i)
        l[i] = i - 1, r[i] = i + 1;
    l[1] = r[n] = -1, r[1] = 2, l[n] = n - 1;
    priority_queue<tuple<ldouble, int, int>> heap;
    for (int i = 1; i < n; ++ i) {
        if (v[i] != v[i + 1]) {
            auto t = solve(i, i + 1);
            if (t > 0) heap.emplace(-t, i, i + 1);
        }
    }
    while (!heap.empty()) {
        auto [_t, ll, rr] = heap.top();
        heap.pop();
        if (dead[ll] || dead[rr]) continue;
        dead.set(ll), dead.set(rr);
        auto nl = l[ll], nr = r[rr];
        if (nl < 0 || nr < 0) continue;
        else r[nl] = nr, l[nr] = nl;
        if (v[nl] != v[nr]) {
            auto nt = solve(nl, nr);
            if (nt > 0) heap.emplace(-nt, nl, nr);
        }
    }
    auto ans = n - dead.count();
    cout << ans << endl;
    for (int i = 1; i <= n; ++ i)
        if (!dead[i]) cout << i << ' ';
    cout << endl;
    return 0;
}