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
int a[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    for (int T = read(); T--;) {
        int n = read();
        for (int i = 1; i <= n; ++i)
            a[i] = read();
        sort(a + 1, a + 1 + n);
        auto cnt = upper_bound(a + 1, a + 1 + n, 0) - a;
        if (cnt > n) {
            write(n), puts("");
            continue;
        } else assert(a[cnt] > 0);
        bool ok = true;
        for (int i = 1; i < cnt; ++ i)
            if (a[i + 1] - a[i] < a[cnt]) {
                ok = false; break;
            }
        if (ok) cout << cnt << endl;
        else cout << cnt - 1 << endl;
    }
    return 0;
}