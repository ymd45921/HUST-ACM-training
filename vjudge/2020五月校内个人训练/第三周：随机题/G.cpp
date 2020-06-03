/**
 *
 * 题目保证每一个数字都是不同的
 *
 * 可以正经的拿线段树，也可以巧妙的使用并查集；
 * 可不可以拿珂朵莉树乱搞呢，感觉不是不行（
 *
 * 这nm竟然也是二分单调性，草==
 * npa（直接回避了记录最小值
 *
 * TODO: 没有彻底的理解，需要再好好看看
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 1e6 + 5;
const int Q = 25005;

struct triple
{
    int l, r, v;
    triple() = default;
    triple(int l, int r, int v) : l(l), r(r), v(v) {}

    bool operator< (const triple &rhs) const
    {
        if(v == rhs.v) return l < rhs.l;
        else return v > rhs.v;
    }
} query[Q], xx[Q];

namespace UFS
{
    using number = int;
    number p[N];

    void init(int n = N)
    {
        for (int i = 0; i < n; ++ i)
            p[i] = i;
    }

    number father(int x)
    {
        return p[x] == x ? x : p[x] = father(p[x]);
    }

    number join(int x, int y)
    {
        return p[father(x)] = p[father(y)];
    }
}

bool check(int mid)
{
    UFS::init();
    for (int i = 1; i <= mid; ++ i)
        xx[i] = query[i];
    sort(xx + 1, xx + 1 + mid);
    int now = xx[1].v, lmax, lmin, rmax, rmin;
    lmin = lmax = xx[1].l, rmin = rmax = xx[1].r;
    for (int i = 2; i <= mid; ++ i)
        if (now == xx[i].v)
        {
            lmin = min(lmin, xx[i].l);
            rmin = min(rmin, xx[i].r);
            lmax = max(lmax, xx[i].l);
            rmax = max(rmax, xx[i].r);
            if (lmax > rmin) return false;
        }
        else
        {
            if (UFS::father(lmax) > rmin) return false;
            for (int j = UFS::father(lmin);; j = UFS::father(j + 1))
                if (j > rmax) break;
                else UFS::join(j, j + 1);
            now = xx[i].v;
            lmin = lmax = xx[i].l, rmin = rmax = xx[i].r;
        }
    return UFS::father(lmax) <= rmin;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
//    freopen(R"(D:\shiroha\Downloads\P2898_2.in)", "r", stdin);

    int n, q, ll, rr, vv;
    cin >> n >> q;
    for (int i = 1; i <= q; ++ i)
        cin >> query[i].l >> query[i].r >> query[i].v;
    ll = 1, rr = q;
    while (ll <= rr)
    {
        auto mid = ll + rr >> 1u;
        if (check(mid)) vv = mid ++, ll = mid;
        else rr = -- mid;
    }
    cout << (vv >= q ? 0 : vv + 1) << endl;

    return 0;
}