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

signed main() {
    int a[1060] = {1, 1, 2, 1, 1, 2, 2, 4, 4};
    int n = read();
    for (int i = 9; i <= n; ++ i) {
        int test = 1;
        int lim = i / 2;
        while (true) {
            bool ng = false;
            for (int j = 1; j <= lim; ++ j) {
                if (test - a[i - j] ==
                    a[i - j] - a[i - j - j])
                { ng = true; break; }
            }
            if (!ng) { a[i] = test; break; }
            else ++ test;
        }
    }
    cout << a[n] << endl;
    return 0;
}