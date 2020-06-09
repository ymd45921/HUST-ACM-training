/**
 *
 * 悬线法？这里用的是单调栈
 */
#include <iostream>
#include <queue>
#include <functional>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 1050;
char map[N][N];
int n, m, pos[N][N];

namespace MonoStack
{
    using ints = std::pair<int, int>;
    ints s[N]; int top = -1;
    function<bool(int,int)> cmp;
    function<void(ints&)> pushMethod;

    bool empty() {return !~top;}

    ints &front() {return s[top];}

    void push(int first, int second)
    {
        while (~top && cmp(s[top].first, first))
        {
            pushMethod(s[top]);
            -- top;
        }
        s[++ top] = make_pair(first, second);
    }

    [[deprecated("一般来说，单调栈不会手动的弹栈")]]
    void pop() {-- top;}

    void clear() {top = -1;}
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int tmp, _max = 0, px, py, pa, pb, Ax, Ay,
        _ans = 0, sx, sy, sa, sb;

    auto update_max = [&](int val)
    {
        if (val > _max)
        {
            _max = val;
            auto xx = MonoStack::front().first
        }
    };
    auto calc = [&](int x)
    {
        tmp = 0; MonoStack::clear();
        MonoStack::push(pos[x][1], 1);
        for (int i = 2; i <= m; ++ i)
        {
            tmp = 0;
            MonoStack::push(pos[x][i], tmp + 1);
        }
        tmp = 0;
        while (!MonoStack::empty())
        {
            tmp += MonoStack::front().second;
            update_max(MonoStack::front().first * tmp);
        }
        if (_max > _ans)
            _ans = _max, sx = px, sy = py, sa = pa, sb = pb;
    };
    MonoStack::pushMethod = [&](MonoStack::ints &top)
    {
        tmp += top.second;
        update_max(top.first * tmp);
    };
    MonoStack::cmp = [](int a, int b){return a >= b;};

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        cin >> (map[i] + 1);
    memset(pos, 0, sizeof pos);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            if (map[i][j] == '.')
                pos[i][j] = pos[i - 1][j] + 1;
            else if (map[i][j] == 'A')
                pos[i][j] = pos[i - 1][j] + 1,
                Ax = i, Ay = j;
    for (int i = Ax; i <= n; ++ i) calc(i);


    return 0;
}