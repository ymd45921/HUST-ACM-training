
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
#undef bigint

constexpr llong mod = 1e9 + 7;

constexpr lll fast_pow(lll a, lll b = mod - 2) {
    lll ret = 1;
    while (b) {
        if (b & 1) (ret *= a) %= mod;
        (a *= a) %= mod, b >>= 1;
    }
    return ret %= mod;
}

constexpr lll inv6 = fast_pow(6), inv2 = fast_pow(2);

lll sum_i2(lll n) {
    return n * (n + 1) % mod * (2 * n + 1) % mod * inv6 % mod;
}

lll sum_i(lll n) {
    return (n + 1) * n % mod * inv2 % mod;
}

lll xi2(lll l, lll n, lll k) {
    lll ret = 0;
    minimize(n, k);
    for (lll r; l <= n; l = r + 1) {
        if (k / l) r = min(k / (k / l), n);
        else r = n;
        auto val = (k / l) * (k / l) % mod;
        (ret += (r - l + 1) * val % mod) %= mod;
    }
    return ret;
}

lll xi(lll l, lll n, lll k) {
    lll ret = 0;
    minimize(n, k);
    for (lll r; l <= n; l = r + 1) {
        if (k / l) r = min(k / (k / l), n);
        else r = n;
        (ret += (r - l + 1) * (k / l) % mod) %= mod;
    }
    return ret;
}

lll sum_ix(lll n, lll x) {
    auto m = n % x + 1, d = n / x;
    if (!d) return 0;
    lll ret = x * sum_i(d - 1) % mod;
    (ret += m * d % mod) %= mod;
    return ret;
}

lll sum_ix2(lll n, lll x) {
    auto m = n % x + 1, d = n / x;
    if (!d) return 0;
    lll ret = x * sum_i2(d - 1) % mod;
    auto d2 = d * d % mod;
    (ret += m * d2 % mod) %= mod;
    return ret;
}

lll ix(lll l, lll r, lll k) {
    return (sum_ix(r, k) + mod - sum_ix(l - 1, k)) % mod;
}

lll ix2(lll l, lll r, lll k) {
    return (sum_ix2(r, k) + mod - sum_ix2(l - 1, k)) % mod;
}

lll ix_xi(lll l, lll n, lll x1, lll x2) {
    lll ret = 0;
    minimize(n, x2);
    for (lll r; l <= n; l = r + 1) {
        if (x2 / l) r = min(x2 / (x2 / l), n);
        else r = n;
        auto tmp = ix(l, r, x1);
        (ret += tmp * (x2 / l) % mod) %= mod;
    }
    return ret;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    for (auto T = read(); T --;) {
        auto x1 = read(), x2 = read(), y1 = read(), y2 = read();
        auto dy = y2 - y1 + 1, dx = x2 - x1 + 1;
        auto part1 = ix2(x1, x2, x1) + xi2(x1, x2, x2) + ix_xi(x1, x2, x1, x2) * 2;
        auto part2 = ix2(y1, y2, y1) + xi2(y1, y2, y2) + ix_xi(y1, y2, y1, y2) * 2;
        auto part3L = (ix(x1, x2, x1) + xi(x1, x2, x2)) % mod;
        auto part3R = (ix(y1, y2, y1) + xi(y1, y2, y2)) % mod;
        auto part3 = part3L * part3R % mod * 2 % mod;
        auto part12 = (part1 %= mod) * dy % mod + (part2 %= mod) * dx % mod;
        auto ans = (part12 + part3) % mod;
        cout << (llong)ans << endl;
    }
    return 0;
}