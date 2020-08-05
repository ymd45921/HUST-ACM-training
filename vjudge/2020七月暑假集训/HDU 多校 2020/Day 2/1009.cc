/**
 *
 * 发出射线根据交边次数判断某点是否在多边形中
 * 计  算  机  图  形  学 （迫真
 *
 * 一些技巧和需要注意的地方：
 * - 因为 q 很大，访问数组 v 也很大，所以不应该 memset，应浪费空间换标记
 * - 奇怪的标记边界的方法，不太理解），但是需要保证边界的唯一性（
 * 然后代码就可以写出来了 ==
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

const int N = 405, M = N, S = 4e6 + 5;
int w[N][M], v[N * M], sign = 0;
char s[S];
bitset<M> flag[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, m, q, x, y;
    auto solution = [&](int x, int y)
    {
        const auto len = strlen(s);
        int uu = 0, dd = m, ll = n, rr = x;
        auto xx = x, yy = y;
        for (auto &ii : flag) ii.reset();
        for (int i = 0; i < len; ++ i)
        {
            ll > xx && (ll = xx);
            rr < xx && (rr = xx);
            uu < yy && (uu = yy);
            dd > yy && (dd = yy);
            switch (s[i])
            {
                case 'U': ++ yy; break;
                case 'D': -- yy; break;
                case 'L': flag[xx][yy + 1].flip(); -- xx; break;
                case 'R': ++ xx; flag[xx][yy + 1].flip(); break;
            }
        }
        ++ ll, ++ dd;
        uint ans = 0, state = 0;
//      memset(v, 0, sizeof(v));
        ++ sign;
        for (int i = ll; i <= rr; ++ i)
            for (int j = dd; j <= uu; ++ j)
                (state ^= flag[i][j]) &&
                (v[w[i][j]] != sign) &&
                (v[w[i][j]] = sign, ++ ans);
        return ans;
    };
    cin >> t;
    while (t --)
    {
        cin >> n >> m >> q;
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                cin >> w[i][j];
        while (q --)
        {
            cin >> x >> y >> s;
            cout << solution(x, y) << endl;
        }
    }

    return 0;
}