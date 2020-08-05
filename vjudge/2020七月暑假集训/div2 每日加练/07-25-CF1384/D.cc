/**
 *
 * 最近似乎总是拿异或没什么好办法 ==
 * 这种游戏博弈题似乎也只能在草稿纸上模拟讨论（
 *
 * 首先肯定根据每一位进行考虑：
 * 考虑到策略不仅有占优，还可以逼迫对面取劣势
 * 但是后面的策略只有可能在某个最优位包含 2+ 个的时候才可以施展
 * 所以说输赢要看优势位的个数，非优势位的数量
 * 操作空间要求 2+，按照 4 进行考虑
 *
 * - 当某一位有偶数个数字持有时，无论怎么说大家都是一样的
 * - 否则，则一个玩家该位为 0，另一个该位为 1
 * - 可认为焦点就集中在持有该位的数字上
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

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

const int N = 1e5 + 5;

uint a[N], cnt[40];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, key;
    cin >> t;
    while (t --)
    {
        cin >> n;
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < n; ++ i)
        {
            cin >> a[i];
            for (uint j = 0; j < 32; ++ j)
                if (a[i] >> j & 1u) ++ cnt[j];
        }
        for (key = 31; key >= 0; -- key)
            if (cnt[key] & 1u) break;
        if (key < 0) cout << "DRAW" << endl;
        else
        {
            auto xx = cnt[key], yy = n - xx;
            if (yy & 1u) cout << "WIN" << endl;
            else cout << (xx & 2u ? "LOSE" : "WIN") << endl;
        }
    }

    return 0;
}