/**
 *
 * 有点意思，确实事没有想到，思维能力还是拉了
 *
 * 首先，考虑现在存在一个最小的 m，使得 a[m]/m 最小；
 * 所以，既然希望能量更少，所以肯定是要尽可能地选择这个 m 号物品；
 * 但是因为 m 不一定是 1，所以并不是能凑成所有可能的 k
 *
 * 但是这里由抽屉原理可以知道，如果你选择了不少于 m 个正整数，那么——
 * 这堆数字中，一定有一个子集的和是 m 的倍数：为什么呢？
 * - 首先，我们考虑每个抽屉都是根据 %m 的值来分类的，那么有 m 个抽屉
 * - 然后，我们按照某种顺序排序这 m 个数字，并求前缀和，可以得到 m 个前缀和
 * - 这样，对前缀和求 % m 就可以得到 m 个余数，且被塞进 [0, m) 个抽屉里
 *   - 如果有一个前缀和 % m === 0，那么这个前缀就满足了这个子集的要求
 *   - 否则，就相当于 m 个值塞入剩下的 [1, m) 共 m - 1 个抽屉里
 *   - 根据抽屉原理，一定有一个抽屉里塞进了两个不同的前缀和，此时就可以做差
 *   - 差的前缀和一定是 0，满足了待求的子集的要求，可以构成子集
 * - 至此，我们已经通过抽屉原理证明了这一结论
 * 因此，只要一个大询问 k 要被分成超过 m 个数字，那么就一定有子集可以被表示为 m 的倍数
 * 而因为 m 的单价最低，所以肯定要使劲选，所以这一部分的子集转化为对应数量的 m 最优
 * 那么，m 个数字可以达到的最大的 k 是什么呢：因为最大数字是 n，所以是 nm
 * 实际上，因为我们的数字还满足连续的性质，实际上可能的限制更小（猜想，我也不会证明）
 *
 * 但是，还因为这个题目要求一旦分解到小于 n 就不能再分解，所以：
 * 考虑分解过程是一颗树，那么所有的叶子节点都是小于 n 的，而所有的非叶子都是 > n 的
 * 那么，整棵树中至少有两个叶子节点的值的和 > n，否则无法画出这颗树
 * 也就是说，对于 k，分解并不自由；但是相应的，如果除去这两个节点，剩下来的部分无限制
 *
 * 接下来综合上面的两个结论：
 * - 因为 m 个数字一定可以凑出 m 的倍数，所以 m - 1 个数字可能凑不出 m 的倍数
 * - 因为分解还要求两个叶子节点的和 > n，所以有两个数字的分解是受到其限制的
 * - 因此，不能使用 m 的倍数优化的最大数字是 (m - 1)n + 2n，这部分需要 DP 做
 * 而大于这部分的数字？因为一定可以用 m 优化，所以优化到这个范围内就可以了
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

const int N = 110, M = 12315;
llong a[N], f[M], inf = 1e18;

bool compare(int i, int j) {
    auto ii = a[i] * j, jj = a[j] * i;
    if (ii == jj) return i < j;
    else return ii < jj;
}

signed main() {
    int n = read(), q = read(), _[N];
    for (int i = 1; i <= n; ++ i) a[i] = read();
    iota(_, _ + n, 1);
    auto m = *min_element(_, _ + n, compare);
    auto lim = (m + 1) * n;
    fill(f + 1, f + 1 + lim, inf);
    memcpy(f + 1, a + 1, sizeof(llong) * n);
    for (int i = n + 1; i <= lim; ++ i)
        for (int j = 1; j <= n; ++ j)
            f[i] = min(f[i], f[i - j] + a[j]);
    while (q --) {
        int x = read();
        if (x <= lim) printf("%lld\n", f[x]);
        else {
            int t = (x - lim + m - 1) / m;
            int mt = m * t, res = x - mt;
            printf("%lld\n", f[res] + a[m] * t);
        }
    }
    return 0;
}