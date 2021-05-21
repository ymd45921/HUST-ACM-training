#pragma GCC optimize(3, "Ofast", "inline")
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
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

using trick = tuple<int, double, int>;
const int N = 5050, M = 110;
double f[M][N], tt[N];
const double eps = 1e-7;

template <typename T>
int sgn(T x) {return x < 0 ? -1 : x > 0;}

int compareTo(double a, double b) {
    return fabs(a - b) < eps ? 0 : sgn(a - b);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, r, m;
    cin >> n >> r >> m;
    vector<trick> ts(n + 2);
    ts[0] = make_tuple(0, 1.0, 0);
    ts[m + 1] = make_tuple(n, 1.0, 0);
    for (int i = 1; i <= m; ++ i) {
        auto &[t, p, d] = ts[i];
        cin >> t >> p >> d;
        tt[i] = t - get<0>(ts[i - 1]);
    }
    tt[m + 1] = n - get<0>(ts[m]);
    const int margin = r - n - 1;
    const auto binary = [&](double f00) {
        for (int i = m; i >= 0; -- i)
            for (int j = 0; j <= margin; ++ j) {
                auto [t, p, d] = ts[i];
                f[i][j] = p * (tt[i + 1] + f[i + 1][j]);
                if (j + d > margin) f[i][j] += (1 - p) * f00;
                else f[i][j] += (1 - p) * min(f00, tt[i + 1] + d + f[i + 1][j + d]);
            }
        return compareTo(f00, f[0][0]) < 0;
    };
    double ll = 0, rr = 3e18;
    while (compareTo(ll, rr) < 0) {
        auto mm = (ll + rr) / 2;
        if (binary(mm)) ll = mm;
        else rr = mm - eps;
    }
    cout << fixed << setprecision(7) << ll << endl;
    return 0;
}
#pragma clang diagnostic pop