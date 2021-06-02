#include <string>
#include <vector>
#include <iostream>

using namespace std;
using llong = long long;

#define int llong

const int N = 4e5 + 5;
int a[N], b[N], cnt[100], it[100];

void depart(int x) {
    for (int & i : cnt) {
        if (!x) return;
        i += x % 2;
        x /= 2;
    }
}

signed main() {
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        cin >> a[i];
        depart(a[i]);
    }
    for (int i = 1; i <= m; ++ i) {
        cin >> b[i];
        ++ it[63 - __builtin_clzll(b[i])];
    }
    for (int i = 0; i < 32; ++ i) {
        if (!it[i]) continue;
        if (cnt[i]) {
            auto ded = min(cnt[i], it[i]);
            cnt[i] -= ded, it[i] -= ded, ans += ded;
        }
        for (int j = i + 1; j < 32; ++ j) {
            if (!it[i] || !cnt[j]) continue;
            int mul = 1 << (j - i);
            auto ded = min(cnt[j] * mul, it[i]);
            auto cost = ded / mul + !!(ded % mul);
            cnt[j] -= cost, it[i] -= ded, ans += ded;
            if (ded % mul) {
                auto siz = ded % mul;
                depart((mul - siz) * (1 << i));
            }
        }
    }
    cout << ans << endl;
}
