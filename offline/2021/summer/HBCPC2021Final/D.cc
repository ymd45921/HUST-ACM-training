#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
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

#define bigint lll
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

const int N = 5050, M = 1e6 + 5;
int a[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    for (int T = read(); T --;) {
        int n = read(), comp = 0;
        llong ans = 0;
        bitset<N> in;
        for (int i = 1; i <= n; ++ i) a[read()] = i;
        for (int l = 1; l < n; ++ l) {
            in.reset(), comp = 1, in.set(a[l]);
            for (int r = l + 1; r <= n; ++ r) {
                bool ll = in[a[r] - 1], rr = in[a[r] + 1];
                comp += 1 - ll - rr;
                in.set(a[r]);
                if (comp <= 2) ++ ans;
            }
        }
        write(ans + (n == 1 ? 0 : n)), puts("");
    }
    return 0;
}
#pragma clang diagnostic pop