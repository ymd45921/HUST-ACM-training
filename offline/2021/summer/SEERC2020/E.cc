
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

const int N = 5e5 + 5;
int a[N], f[N][3][3];
int cnt[3][3];
constexpr pair<int, int> en[] = {{1, 0}, {0, 1}, {0, 0}};

signed main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    auto n = read();
    for (int i = 1; i <= n; ++ i)
        a[i] = (int)read() % 3;
    int cnt1 = 0, cnt2 = 0;
    llong ans = 0;
    cnt[0][0] = 1;
    for (int i = 1; i <= n; ++ i) {
        if (a[i]) ++ (a[i] == 1 ? cnt1 : cnt2);
        cnt1 %= 3, cnt2 %= 3;
        for (auto [p, q] : en) {
            auto x = (cnt1 + 3 - p) % 3;
            auto y = (cnt2 + 3 - q) % 3;
            ans += cnt[x][y];
        }
        ++ cnt[cnt1][cnt2];
    }
    cout << ans << endl;
    return 0;
}