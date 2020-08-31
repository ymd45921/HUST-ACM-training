/**
 *
 * 感觉上的主导权转换似乎炸了（
 *
 * 先手的必胜态：只剩下一个数字的时候先手操作
 * 转化过程：
 * - 前一个数字大于 1，先手可以保持当前状态（当必胜是保持，否则对面也不会允许调转
 * - 前一个数字等于 1，必胜态转化为必败态
 * - 推到第一个数字，当前的主动权持有者必败/必胜
 * ……确实没怎么归纳清楚，但是也没有必要去归纳
 * 只要主导权在手，且至少有一个可控制位置，就可以决定胜负
 * 因为我可以参考后面的石子数量来决定是否恰到好处的让出主导权
 * 这一定是可行的，因为存在必胜状态和必败状态
 *
 * 为什么啊，我一开始就是这么想的为啥样例错了
 * 查了之后重写一遍就又对了？
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
int a[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n;
    cin >> t;
    while (t --)
    {
        cin >> n;
        for (int i = 1; i <= n; ++ i) cin >> a[i];
        uint cnt = 0, win = 1;
        for (int i = 1; i < n; ++ i)
            if (a[i] == 1) win ^= 1u; else break;
        cout << (win ? "First" : "Second") << endl;
    }

    return 0;
}