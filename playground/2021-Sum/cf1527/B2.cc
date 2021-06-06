//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>

using namespace std;
using llong = long long;
using lll = __int128;

#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

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

const int N = 1050;
char s[N], r[N];

signed main() {
#ifndef ONLINE_JUDGE
    freopen("/home/nanami/CLionProjects/untitled/input.txt", "r", stdin);
#endif
    for (int T = read(); T --;) {
        int n = read(), d = 0, x = 0;
        scanf("%s", s + 1);
        strcpy(r + 1, s + 1);
        reverse(r + 1, r + 1 + n);
        for (int i = 1; i <= n; ++ i)
            if (s[i] == '0' && r[i] == '1') ++ d;
            else if (s[i] == '0') ++ x;
        bool cen = n % 2 && s[n / 2 + 1] == '0';
        int bob, alice;
        if (cen) {
            bob = x / 2 + d;
            alice = x / 2;
            if (alice) ++ bob;
            else ++ alice;
        } else {
            bob = d, alice = 0;
            int ta = x / 2, tb = x / 2;
            if (x / 2) ++ ta, -- tb;
            if (d && alice + ta >= bob + tb) {
                -- bob, ++ alice;
                swap(ta, tb);
            }
            alice += ta, bob += tb;
        }
        cerr << alice << ' ' << bob << endl;
        if (alice == bob) puts("DRAW");
        else puts(alice < bob ? "ALICE" : "BOB");
    }
    return 0;
}