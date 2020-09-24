/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <array>
#include <unordered_map>

#define VAR(var) ""#var" = " << var

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

const int N = 1e5 + 5;
longs dp[N][6];
unordered_map<char, string> mm[6];
string s;

inline void mov(int x)
{
    int a = x - 1, b = x;
    char aa = s[a - 1], bb = s[b - 1];
    if (aa == bb)
    {
        for (int i = 0; i < 6; ++ i)
            dp[b][i] = dp[a][i];
        return;
    }
    for (int j = 0; j < 6; ++ j)
    {
        dp[x][j] = 0x3f3f3f3f3f3f3f3f;
        for (int i = 0; i < 6; ++ i)
        {
            auto add = 0;
            if (mm[i][aa][1] == mm[j][bb][0] &&
                mm[i][aa][2] == mm[j][bb][1])
                add = + 1;
            else if (mm[i][aa][2] == mm[j][bb][0])
                add = + 2;
            else add = + 3;
//            cerr << VAR(mm[i][aa]) << ", "
//                 << VAR(mm[j][bb]) << ", "
//                 << VAR(add) << endl;
            dp[x][j] = min(dp[x][j], dp[x - 1][i] + add);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto &m = mm[0];
    m['Y'] = "QQQ", m['V'] = "QQW", m['G'] = "QQE", m['C'] = "WWW", m['X'] = "QWW";
    m['Z'] = "WWE", m['T'] = "EEE", m['F'] = "QEE", m['D'] = "WEE", m['B'] = "QWE";
    for (auto &ii : m)
    {
        for (int i = 1; i < 6; ++ i)
            mm[i][ii.first] = m[ii.first];
        swap(mm[1][ii.first][1], mm[1][ii.first][2]);
        swap(mm[2][ii.first][0], mm[2][ii.first][1]);
        mm[3][ii.first] = mm[2][ii.first];
        swap(mm[3][ii.first][1], mm[3][ii.first][2]);
        mm[4][ii.first] = mm[1][ii.first];
        swap(mm[4][ii.first][0], mm[4][ii.first][1]);
        mm[5][ii.first] = mm[4][ii.first];
        swap(mm[5][ii.first][1], mm[5][ii.first][2]);
    }
    cin >> s;
    for (int i = 0; i < 6; ++ i) dp[1][i] = 3;
    auto siz = s.length();
    for (int i = 1; i < siz; ++ i) mov(i + 1);
    longs ans = dp[siz][0];
    for (int i = 1; i < 6; ++ i)
        ans = min(dp[siz][i], ans);
    cout << ans + siz << endl;

    return 0;
}