/**
 *
 * 悬线法？这里用的是单调栈
 *
 * 单调栈写不出来了，我爬了，研究hls的代码了；
 * 之所以这个代码看起来很暴力，是因为它只关注从 A 出发的矩阵
 * 这和一般的 0, 1 最大子矩阵问题不同。
 * 一般的问题的方法（单调栈）遍历每一个节点为底边上的“中点”，所以统计这个加速很大；
 * 就算这个点不是真正的“中心点”，下面的点也一定会包括这种情况.
 *
 * 推测单调栈写法：单调栈可以得到 A 的向上的最高距离，和左右界；
 * 从当前行开始向下遍历行，对于这个左右界之内的所有点，找到它的“最大矩形”；
 * 计算这个矩形的上下左右边界，判断 A 点是否包含在内，并更新记录。
 */
#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 1050;
char map[N][N], ans[N][N];
int n, m, pos[N][N];

struct node
{
    int x, y; char ch;
    node(int x, int y, char ch) : x(x), y(y), ch(ch) {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int Ax, Ay;             // 王子 'A' 的坐标
    vector<node> vec;       // 存储其他的王子的坐标以及字母
    pair<int, int> seg[N];  // Ax 行上每一个位置的上下界
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        cin >> (map[i] + 1);
    memset(pos, 0, sizeof pos);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            if (map[i][j] == 'A')
                pos[i][j] = map[i][j] - 'A' + 1,
                Ax = i, Ay = j;
            else if (map[i][j] != '.')
                pos[i][j] = map[i][j] - 'A' + 1,
                vec.emplace_back(i, j, pos[i][j] - 1 + 'a');
    for (int j = 1; j <= m; ++ j)                      // 上下拓展 Ax 行的全部列
    {
        int uu = Ax, dd = Ax;
        if (pos[Ax][j] && j != Ay)                     // 当前位置有其他王子
        {
            seg[j] = make_pair(uu, dd - 1);         // 不可拓展，塞一个空区间进去
            continue;
        }
        while (uu > 1 && !pos[uu - 1][j]) -- uu;
        while (dd + 1 <= n && !pos[dd + 1][j]) ++ dd;
        seg[j] = make_pair(uu, dd);                    // 记录当前列最大拓展范围
    }
    pair<int, int> outer = seg[Ay], sav;               // sav 记录 A 矩阵的上下边界
    int al = Ay, ar = Ay, aa = 0;                      // al，ar 记录 A 矩阵的左右边界
    for (int ll = Ay; ll >= 1; -- ll)                  // 左右拓展 Ay 列的全部行
    {
        auto inner = outer;
        for (int rr = Ay; rr <= m; ++ rr)
        {
            int area = (rr - ll + 1) * (inner.second - inner.first + 1);
            if (area > aa)
            {
                aa = area, al = ll, ar = rr;
                sav = inner;
            }
            inner.first = max(inner.first, seg[rr + 1].first);      // 更新上界
            inner.second = min(inner.second, seg[rr + 1].second);   // 更新下界
        }
        outer.first = max(outer.first, seg[ll - 1].first);          // 更新上下边界初始值
        outer.second = min(outer.second, seg[ll - 1].second);
    }
    for (int i = 1; i <= n; ++ i)                                   // 初始化画布
        for (int j = 1; j <= m; ++ j)
            ans[i][j] = '.';
    for (int j = al; j <= ar; ++ j)                                 // 填充 A 矩阵
        for (int i = sav.first; i <= sav.second; ++ i)
            ans[i][j] = 'a';
    ans[Ax][Ay] = 'A';
    for (auto &ii : vec) ans[ii.x][ii.y] = ii.ch - 'a' + 'A';
    for (auto &ii : vec)
    {
        int xx = ii.x, yy = ii.y;
        char now = ii.ch;
        if (xx <= sav.second && xx >= sav.first)        // 对于左右两侧的其他王子
        {
            int ll, rr;
            while (yy < m && (yy > al || yy + 1 < al) && ans[xx][yy + 1] == '.')
                ans[xx][++ yy] = now;
            rr = yy, yy = ii.y;
            while (yy > 1 && (yy < ar || yy - 1 > ar) && ans[xx][yy - 1] == '.')
                ans[xx][-- yy] = now;
            ll = yy;                                    // 先拓展水平方向
            while (true)                                // 再拓展垂直方向
            {
                ++ xx;
                if (xx > n || xx > sav.second) break;
                bool flag = true;
                for (int j = ll; j <= rr; ++ j) flag &= ans[xx][j] == '.';
                if (flag) for (int j = ll; j <= rr; ++ j) ans[xx][j] = now;
                else break;
            }
            xx = ii.x;
            while (true)
            {
                -- xx;
                if (xx < 1 || xx < sav.first) break;
                bool flag = true;
                for (int j = ll; j <= rr; ++ j) flag &= ans[xx][j] == '.';
                if (flag) for (int j = ll; j <= rr; ++ j) ans[xx][j] = now;
                else break;
            }
        }
        else                                            // 对于上下两侧的其他王子
        {
            int uu, dd;
            while (xx < n && (xx > sav.second || xx + 1 < sav.first) && ans[xx + 1][yy] == '.')
                ans[++ xx][yy] = now;
            dd = xx, xx = ii.x;
            while (xx > 1 && (xx < sav.first || xx - 1 > sav.second) && ans[xx - 1][yy] == '.')
                ans[-- xx][yy] = now;
            uu = xx;
            while (true)
            {
                ++ yy;
                if (yy > m) break;
                bool flag = true;
                for (int i = uu; i <= dd; ++ i) flag &= ans[i][yy] == '.';
                if (flag) for (int i = uu; i <= dd; ++ i) ans[i][yy] = now;
                else break;
            }
            yy = ii.y;
            while (true)
            {
                -- yy;
                if (yy < 1) break;
                bool flag = true;
                for (int i = uu; i <= dd; ++ i) flag &= ans[i][yy] == '.';
                if (flag) for (int i = uu; i <= dd; ++ i) ans[i][yy] = now;
                else break;
            }
        }
    }
    for (int i = 1; i <= n; ++ i)
        cout << (ans[i] + 1) << endl;

    return 0;
}