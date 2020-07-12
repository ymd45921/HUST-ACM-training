/**
 *
 * 啊这，等等，平衡树是什么方法 ==
 * 这是个思维题
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;
using ulongs = unsigned long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 1600;
int a[N], n, m;

namespace InversionPair
{
    using number = int;
    number arr[N], res[N];
    ulongs cnt = 0;

    auto $$ = [](int lhs, int rhs) {return lhs <= rhs;};

    void init(number *a, int size = 0)
    {
        memcpy(arr, a, sizeof(int) * size);
        cnt = 0;
    }

    void _backfill(int ll, int rr)
    {
        for (int i = ll; i < rr; ++ i)
            arr[i] = res[i];
    }

    void _merge(int ll, int rr)
    {
        auto mid = (ll + rr) / 2;
        auto _l = ll, _r = mid, cur = ll;
        while (cur < rr)
            if (!$$(arr[_l], arr[_r]))
            {
                cnt += (mid - _l);
                res[cur] = arr[_r];
                ++ cur, ++ _r;
                if (_r == rr) break;
            }
            else
            {
                res[cur] = arr[_l];
                ++ cur, ++ _l;
                if (_l == mid) break;
            }
        while (_l < mid) res[cur ++] = arr[_l ++];
        while (_r < rr) res[cur ++] = arr[_r ++];
        _backfill(ll, rr);
    }

    void mergeSort(int ll, int rr)
    {
        auto length = rr - ll;
        if (length < 2) return;
        auto mid = (ll + rr) / 2;
        mergeSort(ll, mid);
        mergeSort(mid, rr);
        _merge(ll, rr);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> a[i];
    InversionPair::init(a, n + 1);
    InversionPair::mergeSort(0, n);
    bool state = InversionPair::cnt & 1u;
    cin >> m; while (m --)
    {
        int l, r;
        cin >> l >> r;
        uint sec = r - l + 1;
        auto tmp = sec * (sec - 1) / 2;
        state ^= tmp & 1u;
        cout << (state ? "odd" : "even") << endl;
    }

    return 0;
}