#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

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

void scan(bigint &x) { x = read(); }
#undef bigint

const int N = 10086, M = N * 2;
int w[120];
using mine = tuple<int, int, int>;
mine mn[N];
llong f[M];

signed main() {
    int m = read(), n = read();
    for_each(w + 1, w + 1 + m, scan);
    for (int i = 1; i <= n; ++ i) {
        auto &[s, e, t] = mn[i];
        s = read(), e = read(), t = read();
    }
    sort(mn + 1, mn + 1 + n);
    for (int i = 1; i <= n; ++ i) {
        auto [s, e, t] = mn[i];
        for (int j = 0; j < s; ++ j)
            maximize(f[s], f[j]);
        maximize(f[e], f[s] + (e - s) * (llong)w[t]);
    }
    cout << *max_element(f, f + M) << endl;
    return 0;
}
#pragma clang diagnostic pop