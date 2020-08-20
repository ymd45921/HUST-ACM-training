/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <cassert>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

int map[30][30], mine[30][30], sum[30][30];
bitset<1280> has;
pair<int, int> tbl[1280];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    for (int i = 1; i <= 29; ++ i)
        for (int j = 1; j <= 29; ++ j)
            if ((i + j) % 2 == 0) map[i][j] = 4;
//    for (int i = 1; i <= 29; i += 2)
//        map[1][i] = map[29][i] = map[i][1] = map[i][29] = 3;
//    map[1][29] = map[1][1] = map[29][29] = map[29][1] = 2;
//    for (int i = 1; i <= 29; ++ i)
//    {
//        for (int j = 1; j <= 29; ++ j)
//            sum[i][j] = sum[i][j - 1] + map[i][j];
//        for (int j = 1; j <= 29; ++ j)
//            sum[i][j] += sum[i - 1][j];
//    }
    for (int r = 1; r <= 25; ++ r)
        for (int c = 1; c <= 25; ++ c)
        {
            auto ans = (r * c + 1) / 2 * 4;
            for (int i = 1; i <= c; ++ i)
            {
                if (map[1][i]) -- ans;
                if (map[r][i]) -- ans;
            }
            for (int i = 1; i <= r; ++ i)
            {
                if (map[i][1]) -- ans;
                if (map[i][c]) -- ans;
            }
            if (ans < 0 || ans >= 1280) continue;
            has[ans] = true, tbl[ans] = {r, c};
        }
    cout << has.count() << endl;
    for (int i = 0; i <= 1000; ++ i)
        if (has[i]) cout << "{" << i << ",  {" << tbl[i].first
                         << ", " << tbl[i].second << "}}," << endl;
    return 0;
}