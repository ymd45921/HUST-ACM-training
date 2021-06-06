#include <bits/stdc++.h>

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
#undef bigint

int a[100], b[100];

signed main() {
    for (int T = read(); T --;) {
        int n = read(), nn = n + n;
        for (int i = 1; i <= nn; ++ i)
            a[i] = read();
        sort(a + 1, a + 1 + nn);
        for (int i = 1; i <= n; ++ i)
            b[i * 2] = a[i], b[i * 2 - 1] = a[nn + 1 - i];
        for (int i = 1; i <= nn; ++ i)
            cout << b[i] << " \n"[i == nn];
    }
    return 0;
}