/**
 *
 * 第一个问确实就是个动态规划…… 唔原来是贪心吗？
 * 第二个问题是没能确定，压实了的最低高度能达到，但是好像也举不出反例。
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

const int N = 1e5 + 5;
pair<int, int> a[N];
map<int, int> h;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int n, l, r;
    cin >> n;
    for (int i = 0; i < n; ++ i)
    {
        cin >> l >> r;
        a[i] = {r, l};
        ++ h[l], -- h[r];
    }
    sort(a, a + n);
    int tail = - 2e8 - 50, cnt = 0;
    for (int i = 0; i < n; ++ i)
        if (a[i].second >= tail)
            tail = a[i].first, ++ cnt;
    int xx = 0, last = 0;
    for (auto &ii : h)
    {
        last += ii.second;
        xx = max(xx, last);
    }
    cout << cnt << ' ' << xx << endl;

    return 0;
}