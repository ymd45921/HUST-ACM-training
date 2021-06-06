#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>

using namespace std;
using llong = long long;
using lll = __int128;

#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

#define bigint __int128
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
llong a[N], pre[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    unordered_map<int, vector<int>> pos;
    for (int T = read(); T --;) {
        int n = read();
        pos.clear();
        lll ans = 0;
        for (int i = 1; i <= n; ++ i)
            pos[a[i] = read()].push_back(i);
        for (auto &[id, lis] : pos) {
            auto siz = lis.size();
            for (int i = 0; i < siz; ++ i)
                pre[i] = lis[i];
            for (int i = 1; i < siz; ++ i) {
                pre[i] += pre[i - 1];
                ans += (lll)pre[i - 1] * (n - lis[i] + 1);
            }
        }
        write(ans), puts("");
    }
    return 0;
}
#pragma clang diagnostic pop