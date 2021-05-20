/**
 * 
 * 从 0 0 出发没有考虑它直接成立，少减了
 */
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

const int N = 1e6 + 1;
llong ii[N];
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
const llong inf = 1e18;

#define valid(x, y) ((x) >= 0 && (x) < N && (y) >= 0 && (y) < N)
#define root(x) (upper_bound(ii, ii + N, (x)) - ii - 1)

signed main() {
#ifndef ONLINE_JUDGE
//    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    for (int i = 1; i < N; ++ i)
        ii[i] = (llong)i * i;
    auto n = read(), x = 0ll, y = 0ll;
    cout << x << ' ' << y << endl;
    auto d = read(), r = min((llong)root(d), (llong)5e5);
    while (n) {
        pair<llong, pair<llong, llong>> tmp(inf, {-1, -1});
        if (r) for (int i = 0; i < 4; ++ i) {
            auto xx = x + dx[i] * r, yy = y + dy[i] * r;
            if (valid(xx, yy)) {
                cout << xx << ' ' << yy << endl;
                auto dd = read();
                if (!dd) if (!-- n) return 0;
                tmp = min(tmp, make_pair(dd, make_pair(xx, yy)));
            }
        } else {
            cout << x << ' ' << y << endl;
            tmp.first = read();
            tmp.second = make_pair(x, y);
        }
        tie(x, y) = tmp.second;
        r = min((llong)root(tmp.first), (llong)5e5);
    }
}