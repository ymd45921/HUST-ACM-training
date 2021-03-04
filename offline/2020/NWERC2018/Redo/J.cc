/**
 *
 * 假设现在除了本人外的最高分有 x 人
 * 这些人的分数一起降低一分需要 log(x) 次数
 * 按照涨分思考容易误入歧途
 * 因为最高分一旦脱离了本人的诅咒，就会一直涨分
 * 从而和其他一般人的分差保持恒定
 * 
 * 形式化一点的说：
 * - 假设某种状态下，除我之外的最高分数量是 x，和第二名差距为 d
 * - 显然经过 lg2(x) 回合之后，最高分全体增加 lg2(x)-1，其他则增加 lg2(x)
 * - 第 lg2(x)-1 回合，一定只有唯一的最高分不增，其他都增加
 * - 换句话说，就是除了我之外的最高分在这样的回合是不上升的
 * - 所以，对于每种最高分局面，回合数以及加的分（缩小的差距）都是可以直接算的
 * - 当某种最高分局面计算完成后，就会和次高分合并，此时扩增即可
 * 当然，比起 lg2(x)-1，使用 lg2(x/2) 更加合理且安全。
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 0;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

const int N = 1e5 + 5;
longs p[N], n;
int lg2[N];

void preLog2(int x)
{
    lg2[2] = 1;
    for (int i = 3; i < N; ++ i)
        lg2[i] = lg2[i / 2] + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using In::read;

    read(n);
    preLog2(n);
    for (int i = 1; i <= n; ++ i)
        read(p[i]);
    sort(p + 1, p + 1 + n);
    reverse(p + 1, p + 1 + n);
    auto me = p[1], xx = p[2], ans = 0ll;
    int cur = 2;
    while (true)
    {
        while (cur + 1 <= n && p[cur + 1] == p[cur]) ++ cur;
        auto cnt = cur - 1, k = lg2[cnt / 2];       // k+1 周期： k回合上升max，1回合缩小d
        auto dx = me - xx, t = dx / (k + 1);        // 计算可以经过的周期数量
        if (cnt == n - 1) 
        {
            xx += k * t;
            ans += (k + 1) * t;
            ans += dx % (k + 1);
        }
        else
        {
            longs d = p[cur] - p[cur + 1];          // 每个周期d只能缩小1，故一共d回合
            if (xx + k * d <= me)                   // 不会超过，则拉平最大次大，进行下一次扩增
            {
                xx += k * d;
                ans += (k + 1) * d;
            }
            else                                    // 否则，只能根据插值计算周期数
            {
                xx += k * t;
                ans += (k + 1) * t;
                ans += dx % (k + 1);
            }
        }
        if (xx > me) break;        
        if (++ cur > n) break;
    }
    printf("%lld\n", ans);

    return 0;
}

