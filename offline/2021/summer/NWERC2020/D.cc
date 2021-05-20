#include <bits/stdc++.h>

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
#undef bigint

const int N = 1e6 + 5;
llong ii[N];

signed main() {
#ifndef ONLINE_JUDGE
//    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    for (int i = 1; i < N; ++ i)
        ii[i] = (llong)i * i;
    auto n = read();
    unordered_map<llong, int> mem;
    while (n) {
        cout << "0 0" << endl;
        llong d = read(), lim = d / 2;
        if (!d) { -- n; continue; }
        for (int i = mem[d]; ii[i] <= lim; ++ i) {
            auto pos = lower_bound(ii, ii + N, d - ii[i]) - ii;
            auto res = ii[pos];
            if (res + ii[i] != d) continue;
            cout << pos << ' ' << i << endl;
            if (!read()) { -- n; mem[d] = i; break; }
            if (res == ii[i]) continue;
            cout << i << ' ' << pos << endl;
            if (!read()) { -- n; mem[d] = i; break; }
        }
    }
}