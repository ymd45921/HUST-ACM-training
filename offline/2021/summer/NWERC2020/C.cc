#include <bits/stdc++.h>

using namespace std;

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

int n, k;
int d, s;

signed main() {
    n = read(); k = read();
    d = read(); s = read();
    if(n == k) printf("impossible\n");
    else {
        long double ans = (long double) (n * d - s * k) / (long double) (n - k);
        if(ans >= 0 && ans <= 100)
            printf("%.7Lf\n", ans);
        else printf("impossible\n");
    }
}