/**
 * 
 * 不 +a 就 -b 的经典偏序关系，以 a+b 作为衡量标准
 * - 要点 1，找到 m+p 是决定性的衡量条件——手里的钱越多越优（贪心）
 * - 要点 2，意识到了抢劫和接济两类人是不相交的——存在明确的界限
 * - 要点 3，发现二分单调性，并且利用这个界限来方便 check
 * 综上所述，就是这个题目的解法
 */
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

#define bigint llong
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

void input(bigint &x) { x = read(); }
#undef bigint

const int N = 1e5 + 5;
llong m[N], p[N], sm[N], sp[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    auto n = read();
    for_each(m + 1, m + 1 + n, input);
    for_each(p + 1, p + 1 + n, input);
    vector<pair<llong, llong>> li;
    for (int i = 1; i <= n; ++ i)
        li.emplace_back(m[i] + p[i], i);
    sort(li.begin(), li.end(), greater<>());
    priority_queue<llong> pp;
    priority_queue<llong, vector<llong>, greater<>> mm;
    const auto check = [&](int k) {
        if (k * 2 > n) return false;
        llong ps = 0, ms = 0;
        while (!mm.empty()) mm.pop();
        while (!pp.empty()) pp.pop();
        for (int i = 0; i < n; ++ i) {
            mm.push(m[li[i].second]);
            ms += m[li[i].second];
            if (mm.size() > k) {
                ms -= mm.top();
                mm.pop();
            }
            sm[i + 1] = ms;
        }
        for (int i = n - 1; i >= 0; -- i) {
            pp.push(p[li[i].second]);
            ps += p[li[i].second];
            if (pp.size() > k) {
                ps -= pp.top();
                pp.pop();
            }
            sp[i] = ps;
        }
        for (auto i = k; i <= n - k; ++ i)
            if (sm[i] >= sp[i]) return true;
        return false;
    };
    auto l = 0, r = (int)n / 2, ans = 0;
    while (l <= r) {
        auto mid = (l + r) / 2;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans << endl;
    return 0;
}