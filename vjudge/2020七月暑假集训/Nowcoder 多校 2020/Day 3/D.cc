/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cassert>

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

const uint sq[] = {0, 1, 4, 9, 16, 25, 36, 49, 56, 81, 100};
const uint bd[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40};
uint cnt[15];

uint atLeast(uint n, uint ii)
{
    auto res = n - sq[ii];
    if (res > ii) return bd[ii] + 4;
    else if (res) return bd[ii] + 2;
    else return bd[ii];
}

uint getIndex(uint n)
{
    auto xx = lower_bound(sq, sq + 11, n);
    return xx - sq;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    uint t, n, m; cin >> t;
    while (t --)
    {
        cin >> n >> m;
        auto ii = getIndex(n);
        auto downTo = atLeast(n, ii);
        auto res = n - sq[ii];
        if (m < downTo || m & 1u || m > 4 * n)
        {
            cout << "No" << endl;
            continue;
        }
        else
        {
            cout << "Yes" << endl;
            if (m == 4 * n) for (uint i = 1; i <= n; ++ i)
                cout << i << ' ' << i << endl;
            else if (m == downTo)
                if (res > ii)
                {
                    auto yy = res - ii;
                    for (uint i = 1; i <= ii + 1; ++ i)
                    {
                        for (uint j = 1; j <= ii; ++ j)
                            cout << j << ' ' << i << endl;
                        if (i <= yy) cout << ii + 1 << ' ' << i << endl;
                    }
                }
                else for (uint j = 1; j <= ii; ++ j)
                {
                    for (uint i = 1; i <= ii; ++ i)
                        cout << j << ' ' << i << endl;
                    if (j <= res) cout << j << ' ' << ii + 1 << endl;
                }
            else
            {
                auto row = ii, col = ii;
                if (res) ++ row;
                if (res > ii) ++ col;
                auto tp = n * 2 + 2;
                if (m >= tp)
                {
                    auto need = (m - tp) / 2;
                    uint top = 1;
                    for (uint i = 1; i <= n; ++ i)
                    {
                        cout << top << ' ' << 1 << endl;
                        ++ top;
                        if (i <= need) ++ top;
                    }
                }
                else
                {
                    auto need = (m - downTo) / 2;
                    auto mm = n;
                    for (int i = 1; i <= col; ++ i)
                        if (mm > row) cnt[i] = row, mm -= row;
                        else cnt[i] = mm;
                    auto top = row + 1;
                    for (int i = col; i > 0; -- i)
                    {
                        cout << 1 << ' ' << i << endl;
                        for (int j = cnt[col]; j > 1; -- j)
                        {
                            if (need)
                            {
                                cout << top << ' ' << 1 << endl;
                                ++ top; -- need;
                            }
                            else cout << j << ' ' << i << endl;
                        }
                    }
                }
            }
        }
    }

    return 0;
}