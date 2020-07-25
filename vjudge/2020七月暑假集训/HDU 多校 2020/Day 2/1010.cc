/**
 *
 * HDU OJ 不支持 $ 命名
 *
 * 确实是个大型暴力（
 * 但是优化比不优化差这么多是我没有想到的 ==
 *
 * 需要保证搜索树每一层节点数至少是上一层的两倍，否则复杂度会退化一个 n
 * 有一说一非常形象：较多种情况确实放在上面更丑陋
 * 因为装备一定比不装备要好，所以并不应该搜索不装备的情况
 * 可以进行最优化剪枝：假设后面的都是最大值 100，若还比答案小就舍弃子树
 *
 * 这个题目实际上有线性做法的（来自 hls
 * 
 * 补题 WA：忘记重置 DFS 找到的最大答案为 0 了。
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

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

struct item
{
    int a, b, c, d;

    friend istream &operator >>(istream &is, item &it)
    { return is >> it.a >> it.b >> it.c >> it.d; }

    item operator +(const item &rhs) const
    { return {a + rhs.a, b + rhs.b, c + rhs.c, d + rhs.d}; }
};

vector<item> vec[55];
int ind[55], cnt;

longs global = 0;

longs dfs(int tp, item xx)
{
    constexpr static longs zz = 100;
    if (!tp)
    {
        longs ans = (zz + xx.a) * (zz + xx.b) * (zz + xx.c) * (zz + xx.d);
        return global = max(ans, global);
    }
    else
    {
        auto res = tp * 100ll + zz;
        longs ideal = (res + xx.a) * (res + xx.b) * (res + xx.c) * (res + xx.d);
        if (ideal <= global) return global;
    }
    for (auto & ii : vec[ind[tp]])
        dfs(tp - 1, xx + ii);
    return global;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, k;
    cin >> t;
    while (t --)
    {
        cin >> n >> k;
        for (int i = 1; i <= k; ++ i)
            vec[i].clear();
        global = 0;
        for (int i = 0; i < n; ++ i)
        {
            int tp; cin >> tp;
            vec[tp].emplace_back();
            cin >> vec[tp].back();
        }
        for (int i = cnt = 0; i <= k; ++ i)
            if (!vec[i].empty()) ind[++ cnt] = i;
        auto ans = dfs(cnt, {0, 0, 0, 0});
        cout << ans << endl;
    }

    return 0;
}
