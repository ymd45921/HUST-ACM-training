/**
 *
 * 看起来是找欧拉回路，实际上是找规律题
 *
 * 虽然你不会手写欧拉路的算法，但是可以手推啊
 * 虽然想想实现起来也不是很难，但是还是没有写
 * 
 * 小心 LL
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 1e5 + 5;

longs pre[N], num[N];

void preProcess()
{
    pre[0] = 0;
    for (int i = 0; i < N; ++ i)
    {
        num[i] = i;
        if (i) pre[i] = pre[i - 1] + i;
    }
}

longs getNumber(int n, longs ind)
{
    longs no = ind / 2;
    auto xx = no - pre[n - 1];
    if (xx >= 0) return ind & 1 ? 1 : n;
    auto ii = lower_bound(pre, pre + n, - xx) - pre;
    if (ind & 1) return n - ii;
    if (pre[ii] == -xx) return n;
    return pre[ii] + xx + n - ii;
}

const auto unitTest = [](int n)
{
    auto limit = (longs) n * (n - 1) + 1;
    cerr << '[' << n << "]:\t\t";
    for (auto i = 1; i <= limit; ++ i)
        cerr << getNumber(n, i) << ' ';
    cerr << endl;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    longs t, n, l, r;
    preProcess();
//    unitTest(4);
    cin >> t; while (t --)
    {
        cin >> n >> l >> r;
        for (auto i = l; i <= r; ++ i)
            cout << getNumber(n, i) << ' ';
        cout << endl;
    }


    return 0;
}