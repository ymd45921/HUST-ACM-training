/**
 *
 * 睾级贪心
 * 对于两只奶牛，孰优孰劣还是可以比较的
 * 也就是说：分析两个整体交换的情况
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 1e5 + 5;

struct cow
{
    int t, d;

    bool operator< (const cow &rhs) const
    { return t * rhs.d < d * rhs.t; }
} c[N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> c[i].t >> c[i].d;
    sort(c, c + n);
    longs ans = 0, t = 0;
    for (int i = 0; i < n; ++ i)
    {
        ans += t * c[i].d;
        t += c[i].t * 2;
    }
    cout << ans << endl;

    return 0;
}