/**
 *
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

const int N = 2e6 + 5;
string s;
int ans[10][10], dis[10][10];

int solve(int ii, int jj)
{
    memset(dis, 0x3f, sizeof dis);
    for (int i = 0; i < 10; ++ i)
    {
        dis[i][(i + ii) % 10] = 1;
        dis[i][(i + jj) % 10] = 1;
    }
    for (int k = 0; k < 10; ++ k)
        for (int i = 0; i < 10; ++ i)
            for (int j = 0; j < 10; ++ j)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    int ret = 0, len = s.length();
    for (int i = 1; i < len; ++ i)
    {
        auto x = s[i - 1] - '0', y = s[i] - '0';
        if (dis[x][y] >= inf) return -1;
        else ret += dis[x][y] - 1;
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> s;
    for (int i = 0; i < 10; ++ i)
    {
        for (int j = 0; j < 10; ++ j)
            cout << (ans[i][j] = solve(i, j)) << ' ';
        cout << endl;
    }

    return 0;
}