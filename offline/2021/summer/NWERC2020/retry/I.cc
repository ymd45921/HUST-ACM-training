/**
 *
 * 数据不大，首先考虑暴力；但是我们发现直接暴力是 n³·n 的，太慢了
 * 这个时候，注意到只要有两个人冲突了，那么，整个方案就冲突了
 * 所以，我们可以暴力两个人的情况，然后全部存起来；询问就是 O(1) 的了
 * 因为要找到一组不冲突的情况，这样的询问要进行 n³ 次，做完了（
 *
 * 绝了
 * 对着没问题的代码 De 了半天 bug（（（
 * 在这个题里面，搭边不算相交，不冲突）
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

const int N = 405;
array<bitset<N>, N> ab, ac, bc;
int d[N], a[N], b[N], c[N];
llong iil[N], iir[N], jjl[N], jjr[N];

#define step(x) ((x) % n + 1)
#define assign(x) (x##x##l[x] = x##l, x##x##r[x] = x##r)
#define calcL(x) (x##l = x##r + d[x])
#define calcR(x) (x##r = x##l + x##t[x])

bool simulator(const int *it, const int *jt,
               int i0, int j0, int n) {
    if (i0 == j0) return true;
    int i = i0, j = j0;
    llong il = 0, jl = 0, ir, jr;
    calcR(i), calcR(j);
    for (int t = 0; t < n; ++ t) {
        assign(i), assign(j), calcL(i), calcL(j);
        i = step(i), j = step(j), calcR(i), calcR(j);
    }
    for (int x = 1; x <= n; ++ x)
        if (iil[x] < jjr[x] && jjl[x] < iir[x])
            return true;
    return false;
}

signed main() {
    int n = read();
    for (int i = 1; i <= n; ++ i) d[i] = read();
    for (int i = 1; i <= n; ++ i) a[i] = read();
    for (int i = 1; i <= n; ++ i) b[i] = read();
    for (int i = 1; i <= n; ++ i) c[i] = read();
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j) {
            ab[i][j] = simulator(a, b, i, j, n);
            ac[i][j] = simulator(a, c, i, j, n);
            bc[i][j] = simulator(b, c, i, j, n);
        }
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            for (int k = 1; k <= n; ++ k)
                if (!(ab[i][j] || ac[i][k] || bc[j][k]))
                    return printf("%d %d %d\n", i, j, k), 0;
    puts("impossible");
    return 0;
}