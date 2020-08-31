/**
 *
 * 好难，但是好巧妙
 * 
 * 仔细想清楚吧，看了答案也没有手推了
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
typedef unsigned int uint;
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

const int N = 1050;
pair<uint, uint> p[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    vector<uint> ans;
    uint cnt[2][2], &p00 = cnt[0][0], &p11 = cnt[1][1],
         &p01 = cnt[0][1], &p10 = cnt[1][0];
    uint n, x, y, msk = 1;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> x >> y;
        p[i] = make_pair(x, y);
    }
    while (true)
    {
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; ++ i)
            ++ cnt[bool(p[i].first & msk)][bool(p[i].second & msk)];
        if (p01 + p10 && p00 + p11)         // 4 set : cross
        {
            for (int i = 1; i <= n; ++ i)
                if ((p[i].first & msk) ^ (p[i].second & msk))
                    ans.push_back(i);
            break;
        }
        else if (p00 + p01 && p10 + p11)    // 2 set : half
        {
            for (int i = 1; i <= n; ++ i)
                if (p[i].first & msk) ans.push_back(i);
            break;
        }
        else msk <<= 1u;                    // 1 set : shift mask
    }
    cout << ans.size() << endl;
    for (auto &ii : ans) cout << ii << ' ';
    cout << endl;

    return 0;
}