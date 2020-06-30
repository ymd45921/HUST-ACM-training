/**
 *
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
int n, k, a[N], m[N];

bool check(int fa)
{
    int kk = k, lim = n - 1;
    m[0] = a[0];
    for (int i = 0; i < lim; ++ i)
    {
        if (a[i + 1] - m[i] > fa)
        {
            m[i + 1] =
        }
    }
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    cin >> n >> k;
    int ma = - 1e9, mi = 1e9;
    for (int i = 0; i < n; ++ i)
        cin >> a[i], ma = max(ma, a[i]), mi = min(mi, a[i]);
    int ll = 0, rr = ma - mi + 1, ans;
    while (ll <= rr)
    {
        auto mid = (ll + rr) / 2;
        if (check(mid)) ans = mid, rr = mid - 1;
        else ll = mid + 1;
    }
    cout << ans << endl;

    return 0;
}