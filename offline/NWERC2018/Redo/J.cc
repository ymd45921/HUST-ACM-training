/**
 *
 * 假设现在除了本人外的最高分有 x 人
 * 这些人的分数一起降低一分需要 log(x) 次数
 * 按照涨分思考容易误入歧途
 * 因为最高分一旦脱离了本人的诅咒，就会一直涨分
 * 从而和其他一般人的分差保持恒定
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
    for (int i = 3; i <= N; ++ i)
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
        if (cur == n)
        {
            auto cnt = lg2[cur - 1];
            auto dis = me - xx, a = dis / cnt;
            xx += a * cnt;
            ans += (cnt + 1) * a;
            ans += dis % cnt;
            break;
        }
        else
        {
            longs d = p[cur] - p[cur + 1];
            auto cnt = lg2[cur - 1];
            if (cnt * d + xx <= me)
            {
                xx += cnt * d;
                ans += (cnt + 1) * d;
            }
            else
            {
                longs dis = me - xx, a = d / cnt;
                xx += a * cnt;
                ans += (cnt + 1) * a;
                ans += dis % cnt;
                break;
            }
        }
        if (++ cur > n) break;
    }
    printf("%lld\n", ans);

    return 0;
}

