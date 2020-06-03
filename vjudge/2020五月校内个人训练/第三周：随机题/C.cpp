/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

char map[1000][1000], my[10][10];

void fill(int ii, int jj, int ss)
{
    for (int i = 0; i < ss; ++ i)
        for (int j = 0; j < ss; ++ j)
            map[i + ii][j + jj] = '*';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int n, k, m, p[10];
    cin >> n >> k; m = pow(n, k);
    p[0] = 1, p[1] = n;
    for (int i = 2; i <= k; ++ i)
        p[i] = p[i - 1] * n;
    for (int i = 1; i <= m; ++ i)
    {
        for (int j = 1; j <= m; ++ j)
            map[i][j] = '.';
        map[i][m + 1] = '\0';
    }
    for (int i = 0; i < n; ++ i)
        cin >> (my[i]);
    for (int i = 0; i < k; ++ i)
    {
        auto xx = p[k - i];
        int yy = pow(n, i) - 1;
        for (int ii = 0; ii <= yy; ++ ii)
            for (int jj = 0; jj <= yy; ++ jj)
            {
                auto step = xx / n;
                auto xxx = ii * xx;
                auto yyy = jj * xx;
                for (int iii = 0; iii < n; ++ iii)
                    for (int jjj = 0; jjj < n; ++ jjj)
                        if (my[iii][jjj] == '.') continue;
                        else fill(xxx + 1 + iii * step, yyy + 1 + jjj * step, step);
            }
    }
    for (int i = 1; i <= m; ++ i)
        cout << (map[i] + 1) << endl;

    return 0;
}