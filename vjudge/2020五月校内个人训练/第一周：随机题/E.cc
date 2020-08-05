/**
 *
 * 算是个找规律
 * 
 * 反正只要包含最小的那一组就行了，其实只需要构造两行
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

const int N = 305;
int mat[N][N];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, now = 0;
    cin >> n;
    for (int j = 0; j < n; ++ j)
        if (j & 1)
            for (int i = 0; i < n; ++ i)
                mat[i][j] = ++ now;
        else for (int i = n - 1; i >= 0; -- i)
            mat[i][j] = ++ now;
    for (int i = 0; i < n; ++ i)
    {
        for (int j = 0; j < n; ++ j)
            cout << mat[i][j] << ' ';
        cout << endl;
    }

    return 0;
}