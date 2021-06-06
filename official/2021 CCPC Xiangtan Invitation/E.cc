#include <bits/stdc++.h>

using namespace std;
using llong = long long;

const llong mod = 1e9 + 7;

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
#undef bigint

llong fastPow(llong a, llong b) {
    llong ans = 1;
    while (b) {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

int mem[] = {0, 0, 0, 0, 1, 4, 12, 31};

signed main() {
    for (int T = read(); T --;) {
        int n = read();
        if (n <= 7) {
            cout << mem[n] << endl;
            continue;
        }
        llong ans = fastPow(2, n - 4) * (n - 3) % mod;
        llong tmp = fastPow(2, n - 7) * (mod + 1 - fastPow(fastPow(mod - 8, mod - 2), (n - 1) / 3 - 1)) % mod * 24 % mod * fastPow(9, mod - 2) % mod;
        llong ano = fastPow(8, mod - 2) * fastPow(2, n - (n - 1) / 3 * 3 - 1) % mod * (n - (n - 1) / 3 * 3) % mod * fastPow(mod - 1, (n - 1) / 3 + 1) % mod;
        cerr << "ans = " << ans << ", tmp = " << tmp << ", ano = " << ano << endl;
        llong xx = (ans + tmp + ano) % mod * 8 % mod * fastPow(9, mod - 2) % mod;
        cout << xx << endl;
    }
    return 0;
}