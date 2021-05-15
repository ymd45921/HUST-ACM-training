#pragma GCC optimize(3, "Ofast", "inline")
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
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

using llong = long long;

const int N = 2e6 + 5;
char p[N], ans[N];
bitset<N> ins;

llong next_pos(llong id, int n) {
    return (id * id + 1) % n;
}

signed main() {
    for (int T = read(), t = 1; t <= T; ++ t) {
        int n = read();
        scanf("%s", p);
        priority_queue<tuple<int, char, int>> h;
        stack<int> s;
        assert(s.empty() && h.empty());
        const auto append = [&](int id, int dep) {
            s.push(id), ins.set(id);
            auto nid = (int) next_pos(id, n);
            h.emplace(dep, p[nid], nid);
        };
        auto mx = *max_element(p, p + n);
        for (int i = 0; i < n; ++ i)
            if (mx == p[i]) h.emplace(n, p[i], i);
        int depth = n + 1, len = 0;
        while (len < n && !h.empty()) {
            int dep, val, id;
            tie(dep, val, id) = h.top();
            h.pop();
            if (dep < depth) {
                assert(dep + 1 == depth);
                ans[len ++] = (char)val;
                depth = dep, mx = (char)val;
                while (!s.empty()) {
                    ins.set(s.top(), false);
                    s.pop();
                }
                append(id, depth - 1);
            } else if (ins[id] || val < mx) continue;
            else append(id, depth - 1);
        }
        ans[len] = 0, printf("Case #%d: %s\n", t, ans);
    }
    return 0;
}