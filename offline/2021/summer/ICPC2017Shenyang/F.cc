#include <bits/stdc++.h>

using namespace std;

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
    while (x > 9) str[cnt++] = char((x % 10) + 48), x /= 10;
    str[cnt++] = char(x + 48);
    while (cnt--) putchar(str[cnt]);
}
#undef bigint
#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))

__int128 a[1000] = {4, 14};

signed main() {
    int tcase = read();
    __int128 n;
    __int128 x = 14;
    __int128 y = 10;
    __int128 maxx = 1;
    int sum = 2;
    for (int i = 1; i <= 31; i++) {
        maxx = maxx * 10;
    }
    for (int i = 2;; i++) {
        a[i] = 4 * a[i - 1] - a[i - 2];
        if (a[i] > maxx) break;
        sum++;
    }
    while (tcase--) {
        n = read();
        for (int i = 0; i < sum; i++) {
            if (a[i] >= n) {
                write(a[i]);
                puts("");
                break;
            }
        }
    }
    return 0;
}