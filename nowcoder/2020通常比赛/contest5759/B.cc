/**
 *
 * 为什么这个题叫 G++ 14 就炸了，反而 clang++ 11 过了啊？
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;
const longs mod = 998244353;
const int N = 1e5 + 5;

template <int n> struct matrix
{
    longs m[n][n];

    matrix() = default;

    longs &operator()(unsigned i, unsigned j)
    {
        return m[i][j];
    }

    matrix operator+(const matrix<n> &rhs) const
    {
        matrix<n> res;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                res.m[i][j] = (m[i][j] + rhs.m[i][j]) % mod;
        return res;
    }

    matrix &operator+=(const matrix<n> &rhs)
    {
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                m[i][j] = (m[i][j] + rhs.m[i][j]) % mod;
        return *this;
    }

    matrix operator-(const matrix<n> &rhs) const
    {
        matrix<n> res;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                res.m[i][j] = (m[i][j] - rhs.m[i][j] + mod) % mod;
        return res;
    }

    matrix operator-=(const matrix<n> &rhs)
    {
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                m[i][j] = (m[i][j] - rhs.m[i][j] + mod) % mod;
        return *this;
    }

    matrix operator*(const matrix<n> &rhs) const
    {
        matrix<n> res;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j) res.m[i][j] = 0;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < n; ++ j)
                for (int k = 0; k < n; ++ k)
                    res.m[i][j] = (res.m[i][j] + m[i][k] * rhs.m[k][j] % mod) % mod;
        return res;
    }
};

using mat = matrix<2>;
longs a[N];
mat sum[N], p[N];

void preProcess()
{
    p[1](0, 0) = p[1](1, 1) = 1;
    p[1](0, 1) = p[1](1, 0) = 0;
    sum[1] = p[1]; mat xx;
    xx(0, 0) = 3, xx(0, 1) = 2, xx(1, 0) = 1, xx(1, 1) = 0;
    for (int i = 2; i <= N; ++ i)
    {
        p[i] = p[i - 1] * xx;
        sum[i] = sum[i - 1] + p[i];
    }
}

namespace segTree
{
    mat tree[N << 2], lazy[N << 2];

    void upMerge(unsigned root)
    {
        tree[root] = tree[root << 1u] + tree[root << 1u ^ 1u];
    }

    void downSplit(unsigned root, unsigned l, unsigned r)
    {
        auto mid = (l + r) >> 1u;
        lazy[root << 1u] += lazy[root];
        lazy[root << 1u ^ 1u] += lazy[root] * p[mid + 2 - l];
        tree[root << 1u] += sum[mid - l + 1] * lazy[root];
        tree[root << 1u ^ 1u] += (sum[r - l + 1] - sum[mid - l + 1]) * lazy[root];
        memset(lazy[root].m, 0, sizeof(lazy[root].m));
    }

    void build(unsigned root, unsigned l, unsigned r)
    {
        memset(lazy[root].m, 0, sizeof(lazy[root].m));
        tree[root] = lazy[root];
        if (l == r) tree[root](0, 0) = a[l];
        else
        {
            auto mid = (l + r) >> 1u;
            build(root << 1u, l, mid);
            build(root << 1u ^ 1u, mid + 1, r);
            upMerge(root);
        }
    }

    void update(unsigned root, unsigned l, unsigned r,
            unsigned ll, unsigned rr)
    {
        if (ll <= l && r <= rr)
        {
            lazy[root] += p[l - ll + 1];
            tree[root] += sum[r - ll + 1] - sum[l - ll];
        }
        else
        {
            downSplit(root, l, r);
            auto mid = (l + r) >> 1u;
            if (mid >= ll) update(root << 1u, l, mid, ll, rr);
            if (mid < rr) update(root << 1u ^ 1u, mid + 1, r, ll, rr);
            upMerge(root);
        }
    }

    longs query(unsigned root, unsigned l, unsigned r,
            unsigned ll, unsigned rr)
    {
        if (ll <= l && r <= rr) return tree[root](0, 0);
        downSplit(root, l, r);
        auto mid = (l + r) >> 1u;
        longs ans = 0;
        if (mid >= ll) ans = (ans + query(root << 1u, l, mid, ll, rr)) % mod;
        if (mid < rr) ans = (ans + query(root << 1u ^ 1u, mid + 1, r, ll, rr)) % mod;
        return (ans % mod + mod) % mod;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> a[i];
    segTree::build(1, 1, n);
    while (m --)
    {
        int op, ll, rr;
        cin >> op >> ll >> rr;
        if (ll > rr) swap(ll, rr);
        if (op == 1) segTree::update(1, 1, n, ll, rr);
        else cout << segTree::query(1, 1, n, ll, rr) << endl;
    }

    return 0;
}