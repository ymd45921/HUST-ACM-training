#include <bits/stdc++.h>

using namespace std;

__int128 read() {
    __int128 ret = 0;
    int f = 0, ch = getchar();
    for (; !isdigit(ch); ch = getchar())
        if (ch == '-') f = !f;
    for (; isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - 48;
    return f ? -ret : ret;
}

void write(__int128 x) {
    static char str[100];
    if (x < 0) putchar('-'), x = -x;
    int cnt = 0;
    while (x > 9) str[cnt ++] = char((x % 10) + 48), x /= 10;
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}

signed main() {
    int n, a[505];
    for (auto T = read(); T --;) {
        n = read();
        for (int i = 1; i <= n; ++ i) a[i] = read();
        int space = max(a[n] - a[2], a[n - 1] - a[1]) - n + 2;
        write(space), puts("");
    }
    return 0;
}