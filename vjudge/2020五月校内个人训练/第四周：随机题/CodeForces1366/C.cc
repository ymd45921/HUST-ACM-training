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

int map[40][40];
int cnt[100][2];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, n, m;
    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                cin >> map[i][j], ++ cnt[i + j][map[i][j]];
        unsigned xx = n + m + 2, half = xx / 2 - !(xx & 1u);
        int ans = 0;
        for (int i = 2; i <= half; ++ i)
        {
            auto anti = xx - i;
            int c0 = cnt[i][0] + cnt[anti][0],
                c1 = cnt[i][1] + cnt[anti][1];
            ans += min(c0, c1);
        }
        cout << ans << endl;
    }

    return 0;
}