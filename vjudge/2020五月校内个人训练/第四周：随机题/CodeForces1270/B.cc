/**
 *
 * 标准做法：移项得 a[i] ± i
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
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

const int N = 2e5 + 5;
int a[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, n; cin >> t;
    while (t --)
    {
        cin >> n >> a[0];
        int ll = -1, rr = -1;
        for (int i = 1; i < n; ++ i)
        {
            cin >> a[i];
            if (abs(a[i] - a[i - 1]) > 1)
                ll = i, rr = i + 1;
            else continue;
        }
        if (ll == -1 && rr == -1) cout << "NO" << endl;
        else cout << "YES\n" << ll << ' ' << rr << endl;
    }

    return 0;
}