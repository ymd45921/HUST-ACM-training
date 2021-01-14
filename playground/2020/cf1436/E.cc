/**
 *
 * 我们要求的是所有连续子序列的 MEX 组成的序列的 MEX
 * 所以若答案为 x，则没有连续子序列的 MEX = x
 * 若一个连续子序列的 MEX = x，那么它：
 * - 一定不包含 x
 * - 并且还包含了 [1, x) 所有的数字
 * 一定不包含 x 的最大序列的两端一定是 x（或者端点）
 * 所以对于一个数字 i，只需要检查所有被 i 包裹的区间是否包含 [1, i)
 * 如果是，那么 MEX 序列中出现了 i，不是答案，继续检查 i+1
 *
 * 至于如何检查这个序列，可以使用某些数据结构（比如线段树）
 * - 线段树叶子存储的是在某个时刻，值为 K 的数字最后出现的位置
 * - 线段树其他节点维护最小值，也就是值 [l, r] 都出现的最左位置
 * - 这样，我们就可以查询 [1, n] 的值均出现时的最大最左位置
 * 从左到右遍历数组，每次检查 [1, a[i]) 都出现时是否在 [last, i] 区间内
 * 因为我们遍历数组，所以右边界一定可以得到保障，线段树维护了左边界
 * 每次查询如果都出现了，那么 a[i] 会出现在 MEX 序列中，做上标记
 * 查询完毕之后，将节点加入线段树中；最后遍历检查 [last, n] 范围
 *
 * PS: 简单线段树竟然还有这么简单的写法，学到了啊==
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

static class Scanner
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return (char)getchar();}
} scanner;

const int N = 1e5 + 5;
int a[N], last[N];
bitset<N> ok;

namespace SegTree   // 这颗简单的线段树维护了区间的最小值
{
    int tree[N * 4], n;

    void _update(int ii, int l, int r, int pos, int val)
    {
        if (l == r) return void(tree[ii] = val);
        int mid = (l + r) / 2, ll = ii * 2, rr = ll + 1;
        if (pos <= mid) _update(ll, l, mid, pos, val);
        else _update(rr, mid + 1, r, pos, val);
        tree[ii] = min(tree[ll], tree[rr]);
    }

    int _query(int ii, int l, int r, int xl, int xr)
    {
        if (l == xl && r == xr) return tree[ii];
        int mid = (l + r) / 2, ll = ii * 2, rr = ll + 1;
        if (xr <= mid) return _query(ll, l, mid, xl, xr);
        else if (xl > mid) return _query(rr, mid + 1, r, xl, xr);
        else return min(
                _query(ll, l, mid, xl, mid),
                _query(rr, mid + 1, r, mid + 1, xr));
    }

    void update(int pos, int val)
    {_update(1, 1, n, pos, val);}

    int query(int left, int right)
    {return _query(1, 1, n, left, right);}
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = SegTree::n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
    {
        if (a[i] != 1) ok[1] = true;    // 除非全是 1，不然 1 一定出现在 MEX 数列中
        using namespace SegTree;
        if (a[i] > 1 && query(1, a[i] - 1) > last[a[i]]) ok[a[i]] = true;
        last[a[i]] = i;
        update(a[i], i);
    }
    for (int i = 2; i <= n + 1; ++ i)
        if (SegTree::query(1, i - 1) > last[i])
            ok[i] = true;
    int ans = 1;
    while (ok[ans]) ++ ans;
    println(ans);
    return 0;
}

