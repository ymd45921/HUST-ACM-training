/**
 *
 * 实现还是有一定讲究的
 * 如果不使用vector就会多一个log复杂度
 *
 * 话说这种思维题一般不会太卡这个
 * 至于顺序问题，可选项还挺多的
 * 
 * zcs的申必拓扑排序也是一种实现（
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 1e5+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int a[N], n, b[N], now, maxx;
vector<int> p[N];
stack<int> q;                                       // 也可以queue

void fill()
{
    if (!~a[1]) a[1] = 1; maxx = 1;
    for (int i = 2; i <= n; ++ i)
    {
        if (!~a[i]) a[i] = a[i-1]+1;
        maxx = max(maxx, a[i]);
    }
}

void redo(int l, int r, int ii)
{
    if (l > r) return;
    auto ed = p[ii].rend();
    for (auto i = p[ii].rbegin(); i != ed; ++ i)    // 顺序遍历
        if (*i <= r) q.push(*i);                    // 保证倒序出栈
        else break;
    while (!q.empty()) b[q.top()] = now++, q.pop(); // *倒序填值
    const int iii = ii + 1;
    redo(l, p[ii].back()-1, iii);
    int xx = p[ii].back(); p[ii].pop_back();
    while (!p[ii].empty() && p[ii].back() <= r)
    {
        redo(xx + 1, p[ii].back() - 1, iii);
        xx = p[ii].back(); p[ii].pop_back();
    }
    redo(xx + 1, r, iii);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto solution = [&]
    {
        fill(); now = 1;
        for (int i = n; i; -- i)        // 初始化不同层的p数组
            p[a[i]].push_back(i);       // 倒序（从右到左
        redo(1,n,1);
    };

    int t; cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 1; i <= n; ++ i)
            cin >> a[i];
        solution();
        for (int i = 1; i <= n; ++ i)
            cout << b[i] << ' ';
        cout << endl;
    }

    return 0;
}