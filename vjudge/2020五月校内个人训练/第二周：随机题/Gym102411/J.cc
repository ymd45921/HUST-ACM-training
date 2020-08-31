/**
 * 
 * 较低的可能由较高的到达，从最高的开始
 * 将最高的下一步位置可以到达的地方从图中减去
 *
 * 剩下的到达次高位置的值只可能是 1 或者 0
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 550;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, map[N][N], ans[N][N];
    char ch;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
        {
            cin >> ch;
            map[i][j] = ch - '0';
        }
    for (int i = 1; i < n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
        {
            ans[i][j] = map[i][j];
            if (map[i][j]) for (int k = 1; k <= n; ++ k)
            {
                map[i][k] -= map[j][k];
                while (map[i][k] < 0) map[i][k] += 10;
            }
        }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= n; ++ j)
            cout << ans[i][j];
        cout << endl;
    }

    return 0;
}