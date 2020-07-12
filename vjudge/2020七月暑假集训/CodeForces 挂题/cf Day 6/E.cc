/**
 *
 * 难在哪里？因为它两个限制条件是同层次的
 *
 * 这个上界下界的想法有点东西啊==
 * 本质上一个 DP 题目
 *
 * 之所以会被卡掉：未必是单树交错其他颜色
 * 比如： 2 500 400 600 50 450 => 3
 * 所以说不能使用偷懒的方法
 *
 *
 * 使用一般的 DP 方法：
 * - 简单的想法：dp(i, x, y) = 前 i 棵树，使用了 x, y 个梅子，x + y == k
 * - 状态优化后：dp(i, x, y) = 前 i 棵树，还多出了 x, y 个梅子，可以装多少篮子
 * - 进一步省略：x, y 之间存在模数 k 的关系，可以互相表示
 * 这样就可以优先本树匹配，多余的果子超过 k 自动 +1 的方式转移；
 * （其实不太理解）
 *
 * 这种做法是官方题解的做法：
 * - 当上下界不同时，差来自于严格分配后的剩余 _a + _b >= k
 * - 一篮子 k 个，确定了篮子中 $a 的数量，就确定了 $b 的数量
 * - 所以，通过拼篮子的方法得到的篮子，一定有 $a ∈ [k - _b, _a]（其他全严格
 * - 因为未必只拼了一个篮子，所以不能直接特判，要考虑拼多个
 * - 由第二点可知，拼篮子只需要考虑 $a 即可；
 * - 对于每一棵树，拼篮子的 $a, $b 必须小于树上有的 ai, bi
 * - 如果可以拼，那就将得到的使用 $a 的个数的模数标记可行
 * - 这样，就标记得到了采取拼篮子措施时，可以达到的任何 $a 模数
 * - (*) 若任何 [k - _b, _a] 的模数可以被达到，那么就可以弥补这个差值
 * 代码中，遍历 i 和 j 的过程还可以用前缀和优化掉一维
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

struct tree {longs rasp, blue, all;};

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

tree trees[502];
bool dp[502], $dp[502];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, k, a = 0, b = 0;
    cin >> n >> k;
    for (int i = 0; i < n; ++ i)
        cin >> trees[i].rasp >> trees[i].blue,
        a += trees[i].rasp, b += trees[i].blue,
        trees[i].all = trees[i].rasp + trees[i].blue;
    auto up = (a + b) / k, down = a / k + b / k;        // 可证明 |down - up| = 0, 1
    if (up == down) cout << up << endl;
    else
    {
        auto _a = a % k, _b = b % k;
        auto ll = k - _b, rr = _a;          // 需要树莓数量的上下界（模数）
        dp[0] = true;                       // 满足：可以通过使用同一棵树上的梅子转移到
        for (int x = 0; x < n; ++ x)
        {
            memcpy($dp, dp, sizeof(dp));
            for (int i = 0; i < k; ++ i) if ($dp[i])
                for (int $a = 1; $a < k; ++ $a)
                    if ($a <= trees[x].rasp && k - $a <= trees[x].blue)
                        dp[i + $a - (i + $a >= k ? k : 0)] = true;
            for (int i = ll; i <= rr; ++ i) // 可行区间内有可以转移到的情况存在
                if (dp[i]) { cout << up << endl; return 0; }
        }
        cout << down << endl;
    }

    return 0;
}