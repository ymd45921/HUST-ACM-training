#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#pragma GCC optimize(3, "Ofast", "inline")
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
    while (x > 9) str[cnt ++] = char((x % 10) + 48), x /= 10;
    str[cnt ++] = char(x + 48);
    while (cnt --) putchar(str[cnt]);
}
#undef bigint
#define maximize(a, b...) ((a) = max({(a), b}))
#define minimize(a, b...) ((a) = min({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

constexpr double eps = 1e-8;

int compareTo(double a, double b) {
    const auto d = fabs(a - b);
    return d < eps ? 0 : sgn(a - b);
}

constexpr auto N = 40;
using posibility = double[3];
posibility f[N][N][N][N][4];
bitset<4> vis[N][N][N][N];

constexpr auto monarch = 0, rebel = 1, traitor = 2;
enum position { ZG = 0, FZ = 1, ZC = 2, NJ = 3 };
constexpr int camps[] = {monarch, rebel, traitor};
constexpr int from[] = {monarch, rebel, monarch, traitor};

double *dfs(int zg, int zc, int fz, int nj, position now) {
    auto &state = f[zg][zc][fz][nj][now];
    if (vis[zg][zc][fz][nj][now]) return state;
    else vis[zg][zc][fz][nj][now] = true;
    for (auto &ii : state) ii = 0.0;
    if (!fz && !nj) {
        state[monarch] = 1.0;
    } else if (!zg) {
        if (!zc && !fz) state[traitor] = 1.0;
        else state[rebel] = 1.0;
    } else if ((now == ZG && !zg) || (now == FZ && !fz)
            || (now == ZC && !zc) || (now == NJ && !nj)) {
        auto nxt = position((now + 1) % 4);
        auto res = dfs(zg, zc, fz, nj, nxt);
        for (auto camp : camps) state[camp] = res[camp];
    } else {
        auto nxt = position((now + 1) % 4);
        int scenario = 0, hp[] = {zg, fz, zc, nj};
        double p[3] = {0.0, 0.0, 0.0}, high = -1.0;
        const auto pos = from[now];
        const auto test = [&]() {
            auto res = dfs(hp[0], hp[2], hp[1], hp[3], nxt);
            double tmp = res[pos];
            if (compareTo(tmp, high) > 0) {
                scenario = 1, high = tmp;
                for (auto camp : camps)
                    p[camp] = res[camp];
            }
            else if (!compareTo(tmp, high)) {
                ++ scenario;
                for (auto camp : camps)
                    p[camp] += res[camp];
            }
        };
        for (int i = 0; i < 4; ++ i)
            if (hp[i] && from[i] != pos)
                -- hp[i], test(), ++ hp[i];
        for (auto camp : camps)
            state[camp] = p[camp] / scenario;
    }
    return state;
}

signed main() {
    ios::sync_with_stdio(false), cout.tie(nullptr);
    for (int T = read(); T --;) {
        int zg = read(), zc = read(), fz = read(), nj = read();
        auto ans = dfs(zg, zc, fz, nj, ZG);
        printf("%.6lf %.6lf %.6lf\n", ans[0], ans[1], ans[2]);
    }
}
#pragma clang diagnostic pop