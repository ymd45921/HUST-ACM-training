/**
 *
 * 还是有点意思的
 * 虽然不难但是实现起来还是有一些讲究的
 */
#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 1e5 + 5;
set<int> x2y[N], y2x[N];
enum dir {R = 0, D, L, U};
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, x, y;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++ i)
        x2y[i].insert(0);
    for (int i = 1; i <= m; ++ i)
        y2x[i].insert(0);
    auto kk = k;
    while (kk --)
    {
        cin >> x >> y;
        x2y[x].insert(y);
        y2x[y].insert(x);
    }
    int ub = 0, db = n + 1, lb = 0, rb = m + 1;
    longs cnt = 1;
    dir now = R;
    int px = 1, py = 1;
    bool movable = true;
    bool start = true;
    while (movable)
    {
        int delta;
        switch (now)
        {
            case U:
            {
                auto xx = -- y2x[py].lower_bound(px);
                if (xx == y2x[py].end() || *xx <= ub)
                    delta = - (ub + 1 - px);
                else delta = - (*xx + 1 - px);
                px = px - delta; cnt += delta;
                now = R; lb = py; break;
            }
            case R:
            {
                auto xx = x2y[px].upper_bound(py);
                if (xx == x2y[px].end() || *xx >= rb)
                    delta = rb - 1 - py;
                else delta = *xx - 1 - py;
                py = py + delta; cnt += delta;
                now = D; ub = px; break;
            }
            case D:
            {
                auto xx = y2x[py].upper_bound(px);
                if (xx == y2x[py].end() || *xx >= db)
                    delta = db - 1 - px;
                else delta = *xx - 1 - px;
                px = px + delta; cnt += delta;
                now = L; rb = py; break;
            }
            case L:
            {
                auto xx = -- x2y[px].lower_bound(py);
                if (xx == x2y[px].end() || *xx <= lb)
                    delta = - (lb + 1 - py);
                else delta = - (*xx + 1 - py);
                py = py - delta; cnt += delta;
                now = U; db = px; break;
            }
            default: break;
        }
        if (start) start = false;
        else if (delta == 0) movable = false;
    }
    cout << (cnt == (longs)m * n - k ? "Yes" : "No") << endl;

    return 0;
}