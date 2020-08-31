/**
 * 
 */
#include <iostream>
#include <set>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int n, m, p;

/**
 *
 * 珂朵莉树（区间骗分
 *
 * 只有在数据是严格随机的情况下才能保证复杂度，所以很容易被卡
 * 用 set 实现的珂朵莉树的复杂度为 O(nlognlogn)
 * 而用链表实现的复杂度为 O(nlogn)
 */
namespace ODT
{
    template <class T> struct node
    {
        int l, r;
        mutable T val;

        node(int l, int r, const T &v) : l(l), r(r), val(v) {}
        node(int l, int r, const T &&v) : l(l), r(r), val(v) {}
        bool operator<(const node<T> &rhs) const {return l < rhs.l;}
    };

    using number = longs;
    using iter = set<node<number>>::iterator;
    using func = void (*) (iter &, void *);
    set<node<number>> odt;

    /**
     *
     *
     */
    iter _split(int x)
    {
        if (x > n) return odt.end();
        auto it = -- odt.upper_bound(node<number>(x, 0, 0));
        if (it -> l == x) return it;
        const int l = it -> l, r = it -> r;
        const number v = it -> val;
        odt.erase(it);
        odt.insert(node<number>(l, x - 1, v));
        return odt.insert(node<number>(x, r, v)).first;
    }

    /**
     *
     *
     */
    iter split(int x)
    {
        auto it = odt.lower_bound(node<number>(x, 0, 0));
        if (it != odt.end() && it -> l == x) return it;
        const number v = (-- it) -> val;
        const int l = it -> l, r = it -> r;
        odt.erase(it);
        odt.insert(node<number>(l, x - 1, v));
        return odt.insert(node<number>(x, r, v)).first;
    }

    /**
     *
     *
     */
    void assign(int l, int r, number v)
    {
        auto rr = split(r + 1);
        auto ll = split(l);
        odt.erase(ll, rr);
        odt.insert(node<number>(l, r, v));
    }

    /**
     *
     *
     */
    void travel(int l, int r)
    {
        auto rr = split(r + 1);
        auto ll = split(l);
        for (; ll != rr; ++ ll)
        {
            // do some thing ...
        }
    }

    void run(int l, int r, func todo, void *param)
    {
        auto rr = split(r + 1);
        auto ll = split(l);
        for (; ll != rr; ++ ll) todo(ll, param);
    }

    func add = [](iter &it, void *para)
    {
        const number value = *(number*)para;
        it->val = (it->val + value) % p;
    };

    func mul = [](iter &it, void *para)
    {
        const number value = *(number*)para;
        it->val = (it->val * value) % p;
    };

    longs _sum = 0;

    func sum = [](iter &it, void *para)
    {
        _sum = (_sum + it->val * (it->r - it->l + 1)) % p;
    };
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> p;
    longs x, tail = n + 1;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> x;
        ODT::odt.insert(ODT::node<longs>(i, i, x));
    }
    auto last = ODT::node<longs>(tail, -1, -1);
    ODT::odt.insert(last);
    while (m --)
    {
        int op, l, r;
        longs k;
        cin >> op;
        switch (op)
        {
            case 1:
                cin >> l >> r >> k;
                ODT::run(l, r, ODT::add, &k);
                break;
            case 2:
                cin >> l >> r >> k;
                ODT::run(l, r, ODT::mul, &k);
                break;
            case 3:
                cin >> l >> r >> k;
                ODT::assign(l, r, k);
                break;
            case 4:
            {
                cin >> k;
                auto it = ODT::odt.lower_bound(last);
                ODT::odt.erase(it);
                ODT::odt.insert(ODT::node<longs>(tail, tail, k));
                last = ODT::node<longs>(++ tail, -1, -1);
                ODT::odt.insert(last);
                break;
            }
            case 5:
                cin >> l >> r;
                ODT::_sum = 0;
                ODT::run(l, r, ODT::sum, &k);
                cout << ODT::_sum << endl;
                break;
            default: break;
        }
    }

    return 0;
}