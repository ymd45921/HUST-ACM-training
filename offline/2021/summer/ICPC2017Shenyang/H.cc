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
    for (auto T = read(); T --;) {
        auto zg = read(), zc = read(), fz = read(), nj = read();
        
    }
    return 0;
}