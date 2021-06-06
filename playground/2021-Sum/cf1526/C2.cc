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

const int N = 2e5 + 50;
const llong inf = 1e18;
llong a[N];

signed main() {
    auto n = read();
    for_each(a + 1, a + 1 + n, scan);
    llong cnt = 0, pos = 0, neg = 0;
    priority_queue<llong> ded;
    for (int i = 1; i <= n; ++ i)
        if (a[i] >= 0) ++ cnt, pos += a[i];
        else {
            ded.push(-a[i]), neg -= a[i];
            while (neg > pos) neg -= ded.top(), ded.pop();
        }
    cout << cnt + ded.size() << endl;
    return 0;
}