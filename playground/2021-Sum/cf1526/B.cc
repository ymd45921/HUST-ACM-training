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

llong mn[101], fil = 0, xx[11]{1};

llong merge(llong cnt) {
    if (!cnt) return 0;
    auto it = prev(upper_bound(xx, xx + 11, cnt));
    return cnt / *it + merge(cnt % *it);
}

signed main() {
    for (llong i = 11; ; i += 11) {
        auto res = i % 100;
        if (!mn[res]) {
            mn[res] = i, ++fil;
            if (fil == 100) break;
        }
    }
    for (int i = 1; i < 11; ++ i)
        xx[i] = xx[i - 1] * 10 + 1;
    for (int T = read(); T --;) {
        llong x = read();
        auto tmp = mn[x % 100];
        if (tmp <= x) {
            x -= tmp;
            auto y = tmp / 11 + x / 100 / 11 * 10;
            auto cnt = x / 100 % 11;
            puts(cnt > y ? "NO" : "YES");
        } else puts("NO");
    }
    return 0;
}