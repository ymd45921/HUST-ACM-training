/**
 *
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;

const int N = 30;
array<bitset<N>, N> g;
array<array<int, N>, N> m;
void clear()
{
    for (auto &ii : g) ii.reset();
    for (auto &ii : m) for (auto &jj : ii) jj = 0;
}
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dv[] = {0, 1, 2};
int count(int x, int y)
{
    int ret = 0;
    for (int i = 0; i < 8; ++ i)
        if (g[x + dx[i]][y + dy[i]]) ++ ret;
    return ret;
}

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // freopen("in.txt", "r", stdin);

    string s;
    int r, c;

    while (cin >> r >> c)
    {
        clear();
        for (int i = 0; i < r; ++ i)
        {
            cin >> s;
            for (int j = 0; j < c; ++ j)
                if (s[j] == 'X')
                {
                    g[i + 1][j + 1] = true;
                    for (auto x : dv) for (auto y : dv)
                            m[i + x][j + y] += 1;
                    m[i + 1][j + 1] -= 1;
                }
        }
        longs cnt = 0, ans = 0;
//        for (int i = 1; i <= r; ++ i)
//        {
//            for (int j = 1; j <= c; ++ j)
//                if (!g[i][j])
//                {
//                    auto x = count(i, j);
//                    cerr << x << ' ';
//                    cnt += x;
//                }
//                else cerr << "X ";
//            cerr << endl;
//        }
        for (int i = 1; i <= r; ++ i)
            for (int j = 1; j <= c; ++ j)
                if (!g[i][j]) ans += m[i][j];
       for (int i = 1; i <= r; ++ i)
       {
           for (int j = 1; j <= c; ++ j)
               if (g[i][j]) cerr << "X ";
               else cerr << m[i][j] << ' ';
           cerr << endl;
       }
        cout << ans << endl;
    }

    return 0;
}