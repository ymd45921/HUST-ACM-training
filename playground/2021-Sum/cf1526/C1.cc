#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))

using namespace std;
using llong = long long;

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

void scan(bigint &x) { x = read(); }
#undef bigint

const int N = 2050;
const llong inf = 1e18;
llong a[N], f[N];

signed main() {
    auto n = read();
    for_each(a + 1, a + 1 + n, scan);
    fill(f, f + n + 1, -inf), f[0] = 0;
    for (int i = 1; i <= n; ++ i) {
        for (int j = i; j; -- j) if (f[j - 1] >= 0) {
            maximize(f[j], f[j - 1] + a[i]);
        }
    }
    for (int i = n; i >= 0; -- i)
        if (f[i] >= 0) {cout << i << endl; break;}
    return 0;
}