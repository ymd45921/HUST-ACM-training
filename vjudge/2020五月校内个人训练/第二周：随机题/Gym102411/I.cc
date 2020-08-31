/**
 *
 * 日，怎么一股乱搞的气息
 * 有点之前退火的那个平面二分那味了（
 *
 * 不，不是，你不要误会==
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

struct triple
{
    int x, y, h;
    triple(int x, int y, int h) : x(x), y(y), h(h) {}
};

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

vector<triple> p;
int n;

triple solution()
{
    int uu = p[0].y - p[0].h,
        dd = p[0].y + p[0].h,
        ll = p[0].x - p[0].h,
        rr = p[0].x + p[0].h;
    for (auto &ii : p)
    {
        int uuu = ii.y - ii.h,
            ddd = ii.y + ii.h,
            lll = ii.x - ii.h,
            rrr = ii.x + ii.h;
        uu = min(uu, uuu);
        dd = max(dd, ddd);
        ll = min(ll, lll);
        rr = max(rr, rrr);
    }
    auto xx = rr - ll, yy = dd - uu;
    unsigned length = max(xx, yy);
    if (length & 1u) ++ length;
    int height = length >> 1u;
    return {ll + height, uu + height, height};
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> n; int x, y, h;
    for (int i = 0; i < n; ++ i)
    {
        cin >> x >> y >> h;
        p.emplace_back(x, y, h);
    }
    auto ans = n == 1 ? p.front() : solution();
    cout << ans.x << ' ' << ans.y << ' '
         << ans.h << endl;
    return 0;
}