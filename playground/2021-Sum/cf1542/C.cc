/**
 *
 * 显然，这个题目直接找规律硬编码是折磨自己
 * 注意到 f(i) 的数值很小，所以从这里入手
 * 对于某个值 k 满足 f(i) = k，要求了：
 * - i 可以被 lcm(1,...k - 1) 整除
 * - i 不能被 lcm(1,...k) 整除
 * 那么在范围 n 内，这样的数字就可整除减出来
 * 因为 n 的上限摆在这里，所以 lcm 也具有同样的上限
 *
 * 综上，对于某个定值 k = f(i)，对答案造成的贡献是
 * k * (n / lcm(1,...k - 1) - n / lcm(1,...k))
 * 实际求值的时候只需要直接累加即可，并不需要拆分开
 */
#ifndef CLION_DEBUG
#pragma GCC optimize(3, "Ofast", "inline")
#endif
#include <bits/stdc++.h>

using namespace std;
using llong = long long;
using lll = __int128;

#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

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

/*
 * f(odd) = 2;
 * f(even):
 *  ...
 *  % 720720 == 0:  17
 *  % 360360 == 0:  16
 *  % 27720 == 0:   13
 *  % 2520 == 0:    11
 *  % 840 == 0:     9
 *  % 210 == 0:     8
 *  % 30 == 0:      7
 *  else:           4, 5, 4, 5,...
 *      % 4 == 0:   5
 *      % 4 == 2:   4
 */
signed main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
//    freopen("output.txt", "w", stdout);
//    llong sum = 0;
//    for (int i = 1; i < 10000; ++ i) {
//        auto ii = i * 2, fii = 7;
//        if (ii % 2) fii = 2;
//        else while (!(ii % fii)) ++ fii;
//        sum += fii;
//        printf("f(%d) = %d, sum = %lld\n", ii, fii, sum);
//    }
    constexpr llong mod = 1e9 + 7;
    for (auto T = read(); T --;) {
        auto n = read();
        llong ans = 0, lcm = 1;
        for (auto i = 1ll; lcm <= n; ++ i) {
            auto g = gcd(lcm, i);
            lcm = lcm / g * i;
            ans = (ans + n / lcm) % mod;
        }
        ans = (ans + n) % mod;
        cout << ans << endl;
    }
    return 0;
}