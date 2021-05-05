#include <bits/stdc++.h>

using namespace std;

constexpr auto PI = 3.1415926535897932384626l;
constexpr auto r = 1.l, r2 = r * r;
constexpr auto eps = 1e-18l;

bool equals(long double x, long double y) {
    return abs(x - y) <= eps;
}

long double fun(long double h) {
    if (h == 0) return 0.l;
    const auto rh = r - h, rh2 = rh * rh;
    auto ret = rh * (rh / 2. * sqrtl(r2 - rh2) + r2 / 2. * asin(rh / r)
             - PI * r2 / 4.) + 1. / 3. * sqrtl(pow(r2 - rh2, 3));
    ret *= 4 * r / h;
    return ret / PI;
}

map<long double, long double> d2h;
long double h2d[200005];

void preprocess() {
    for (int i = 0; i <= 200000; ++ i) {
        long double hh = i / 100000.;
        auto dd = fun(hh);
        d2h[dd] = hh, h2d[i] = dd;
    }
}

long double get(long double d) {
    auto it = d2h.lower_bound(d);
    if (it != d2h.end()) {
        auto ti = prev(it);
        if (abs(ti->first - d) < abs(it->first - d))
            return ti->second;
        else return it->second;
    } else return -1.l;
}

long double brute(long double d) {
    for (int i = 0; i <= 200000; ++ i)
        if (equals(h2d[i], d)) return i / 100000.l;
    return -1.l;
}

long double binary(long double d) {
    long double ll = 0, rr = 2;
    while (rr - ll > eps) {
        auto mid = (ll + rr) / 2.;
        auto xx = fun(mid);
        if (equals(xx, d)) return mid;
        if (xx < d) ll = mid;
        else rr = mid;
    }
    return -1.l;
}

long double eval(long double d) {
    if (equals(d, 0)) return 0;
    if (d >= 1) return sqrtl(5 - 4 * d + d * d) * PI;
    const auto h = binary(d);
    const auto num = [&]() {
        auto alpha = 2 * acos((r - h) / r);
        auto s = 0.5 * r2 * alpha;
        auto ss = 0.5 * r2 * sin(alpha);
        if (h > r) return ss + s;
        else return abs(s - ss);
    };
    const auto den = [&]() {
        return h / sqrtl(4 * r2 + h * h);
    };
    return num() / den();
}

signed main() {
    preprocess();

    int t;
    long double d;
    cin >> t;
    cout << fixed << setprecision(10);
    while (t --) {
        cin >> d;
        cout << eval(d) << endl;
    }
    return 0;
}