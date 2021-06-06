/**
 *
 * 两个行动最多可以组成多少个不同的位移？
 * 首先，直接选择排序的话是 n² 种，但是因为只要组合，所以砍一半
 * 这还是最理想情况，再考虑到一直在棋盘内，再考虑到难以避免的重复
 * 实际上，可以到达的位置大概是 <= n²/2 的，所以实际上 Alice 很容易回避
 * 如果进行 k 次随机选点验证，那么 Alice 回避失败的概率是很低很低的
 *
 * 仔细计算，除去 n 种自交的情况，剩下的 n(n-1) 种是会被砍半的
 * 因此，最佳情况下可以到达的点数为 n(n-1)/2 + n + n 的
 * 那么，可以证明在 n < 4 的时候，从某点出发是可能到达所有的点的
 * 所以，这些情况可以不尝试闪避，或者逐点测试保证正确性
 *
 * 事实上，这种随机题在数据范围较小的时候暴力已经成为了常识。
 */
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

const int N = 1e5 + 5;
struct coord {
    int x, y;

    coord operator+(coord rhs) const {
        return {x + rhs.x, y + rhs.y};
    }

    coord operator-(coord rhs) const {
        return {x - rhs.x, y - rhs.y};
    }

    bool operator==(coord rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(coord rhs) const {
        return x != rhs.x || y != rhs.y;
    }

    coord() = default;

    coord(int x, int y) : x(x), y(y) {}
} d[N], a, b;

unordered_set<int> ta[N], vis[N];

#define valid(x, y) ((x) > 0 && (x) <= n && (y) > 0 && (y) <= n)

void clear(int n) {
    for (int i = 1; i <= n; ++ i)
        ta[i].clear();
}

bool test(coord S, coord T, int n) {
    if (S == T) return true;
    for (int i = 1; i <= n; ++ i) {
        auto t = S + d[i];
        if (t == T) return true;
        if (valid(t.x, t.y)) ta[t.x].insert(t.y);
    }
    for (int i = 1; i <= n; ++ i) {
        auto t = T - d[i];
        if (valid(t.x, t.y) && ta[t.x].count(t.y))
            return true;
    }
    return false;
}

auto createRandomMachine(int lb, int rb) {
    if (lb > rb) swap(lb, rb);
    uniform_real_distribution<double> dm (lb, rb);
    random_device rd;
    default_random_engine rm(rd());
    return [=]() mutable { return (int) dm(rm); };
}

coord gen(const function<int()>& rand_int) {
    int x = rand_int(), y = rand_int();
    while (vis[x].count(y)) x = rand_int(), y = rand_int();
    return {x, y};
}

signed main() {
    int n = read();
    a.x = read(), a.y = read();
    b.x = read(), b.y = read();
    for (int i = 1; i <= n; ++ i)
        d[i].x = read(), d[i].y = read();
    if (test(a, b, n)) puts("Alice wins");
    else if (n <= 10) {
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j) {
                auto t = coord(i, j);
                if (t != a && t != b) {
                    clear(n);
                    auto res = test(b, t, n);
                    if (!res)  {
                        printf("tie %d %d\n", t.x, t.y);
                        return 0;
                    }
                }
            }
        puts("Bob wins");
    } else {
        vis[b.x].insert(b.y);
        const auto rd = createRandomMachine(1, n + 1);
        for (int tt = 100; tt; -- tt) {
            auto t = gen(rd);
            vis[t.x].insert(t.y), clear(n);
            auto res = test(b, t, n);
            if (!res)  {
                printf("tie %d %d\n", t.x, t.y);
                return 0;
            }
        }
        puts("Bob wins");
    }
    return 0;
}