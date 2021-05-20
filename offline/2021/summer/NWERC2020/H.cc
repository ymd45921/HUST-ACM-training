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

const int N = 1e5 + 5;
int t[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    int n = read();
    for (int i = 1; i <= n; ++ i)
        t[i] = read();
    sort(t + 1, t + 1 + n);
    int mid = n / 2 + 1, l = mid - 1, r = mid + 1;
    cout << t[mid];
    for (int i = 1; i < n; ++ i)
        if (i % 2) cout << ' ' << t[l --];
        else cout << ' ' << t[r ++];
    cout << endl;
}