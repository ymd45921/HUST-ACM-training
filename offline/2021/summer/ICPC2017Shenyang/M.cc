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

const int K = 1050, N = 10005;
const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};
bitset<N> g[N];
vector<pair<int, int>> b;

int all_p(int n) { return 5 * n * n - 4 * n; }

int half_p(int n) { return 5 * n * (n + 1) / 2 - 2 * n - 2; }

signed main() {
    b.reserve(K);
    for (int T = read(), t = 1; t <= T; ++ t) {
        int n = read(), k = read();
        const auto validator = [&](int x, int y) {
            return !(x < 0 || x >= n || y < 0 || y >= n);
        };
        const auto count = [&](int x, int y) {
            int ret = 1;
            for (int di : {0, 1, 2, 3}) {
                int xx = x + dx[di], yy = y + dy[di];
                if (validator(xx, yy)) ++ ret;
            }
            return ret;
        };
        b.clear();
        for (int i = 1; i <= k; ++ i)
            b.emplace_back(read(), read()),
            g[b.back().first].set(b.back().second);
        int num = half_p(n), den = all_p(n);
        for (auto i : b) {
            int x = i.first, y = i.second, d = count(x, y);
            for (int di : {0, 1, 2, 3}) {
                int xx = x + dx[di], yy = y + dy[di];
                if (validator(xx, yy) && !g[xx][yy]) {
                    -- den;
                    if (xx + yy >= n - 1) -- num;
                }
            }
            den -= d;
            if (x + y >= n - 1) num -= d;
        }
        for (auto i : b) g[i.first][i.second] = false;
        int gg = __gcd(num, den);
        num /= gg, den /= gg;
        printf("Case #%d: %d/%d\n", t, num, den);
    }

    return 0;
}