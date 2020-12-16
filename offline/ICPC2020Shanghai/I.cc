/**
 * 
 * 比赛时写的代码只有两个问题：
 * - 应该使用 long long 来存储系数的
 * - 输出前使用神秘的精度修正
 * 这还真是……涉及到我的知识盲区了（
 */
#include<bits/stdc++.h>

using namespace std;

using longs = long long;
using uint = unsigned;

using number = double;

constexpr number PI = 3.1415926535897932384626;

#define int long long

using answer = pair<int, int>;
number toNumber(answer &ans)
{return ans.first * PI + ans.second;}
answer &operator *=(answer &ans, int t)
{
    ans.first *= t, ans.second *= t;
    return ans;
}
answer &operator +=(answer &a, const answer &b)
{
    a.first += b.first, a.second += b.second;
    return a;
}
answer &operator /=(answer &ans, int t)
{
    ans.first /= t, ans.second /= t;
    return ans;
}

auto inCircle(int m)
{
    int x = (int)floor(2 * m / PI) + 1;;
    assert((number)x * PI / m >= 2 && (number)(x - 1) * PI / m <= 2);
    const int sumX = (x - 1) * x / 2;
    const int goD = m - x + 1;
    const int m2 = m * 2;
    return [=](int r) -> answer
    {
        const int d = 2 * r;
        auto duo = make_pair(sumX * 4 * r, (goD * 2 - 1) * d * m2);
        return duo /= 2;
    };
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    const auto f = inCircle(m);
    answer ans = make_pair(0, 0);
    for (int r = 1; r <= n; ++ r)
    {
        auto fr = f(r);
        ans += fr, fr *= 2;
        for (int R = r + 1; R <= n; ++ R)
        {
            auto tmp = fr;
            tmp.second += 4 * m * m * (R - r);
            ans += tmp;
        }
    }
    if (m > 1)
    {
        int single = n * (n + 1) / 2;
        int tmp = single * m * 2;
        ans.second += tmp;
    }
    cerr << ans.first << "π + " << ans.second << endl;
    auto output = toNumber(ans);
    output += output * 1e-7;
    cout << fixed << setprecision(10) << output << endl;
    return 0;
}