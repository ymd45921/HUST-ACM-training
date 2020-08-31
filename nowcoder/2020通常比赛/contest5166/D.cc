/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e3+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

char ch;
int bb[N][N];
int n, m;

namespace SusLineDP
{
    int left[N][N];
    int right[N][N];
    int upper[N][N];
    int __ans = 0;
    int __sqlen = 0, __sqlen2;

    auto a = bb;
    const bool __square = true;

    void init()
    {
        __ans = __sqlen = __sqlen2 = 0;
    }

    void initRead(int i, int j)
    {
        left[i][j] = right[i][j] = j;
        upper[i][j] = 1;
    }

    int update(int i, int j)
    {
        int xx = right[i][j] - left[i][j] + 1;
        int yy = min(xx, upper[i][j]);
        if (__square)
        {
            __sqlen = max(__sqlen, yy);
            return max(__ans, yy * yy);
        }
        else return max(__ans, xx * upper[i][j]);
    }

    int solve()
    {
        for (int i = 1; i <= n; ++ i)
            for (int j = 2; j <= m; ++ j)
                if (a[i][j] == a[i][j - 1])
                    left[i][j] = left[i][j - 1];
        for (int i = 1; i <= n; ++ i)
            for (int j = m - 1; j >= 1; -- j)
                if (a[i][j] == a[i][j + 1])
                    right[i][j] = right[i][j + 1];
        for (int i = 2; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
            {
                if (a[i][j] == a[i - 1][j])
                {
                    left[i][j] = max(left[i][j], left[i - 1][j]);
                    right[i][j] = min(right[i][j], right[i - 1][j]);
                    upper[i][j] = upper[i - 1][j] + 1;
                }
                __ans = update(i, j);
            }
        return __sqlen;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t --)
    {
        SusLineDP::init();
        cin >> n >> m;
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
            {
                cin >> ch;
                bb[i][j] = ch - 'A';
                SusLineDP::initRead(i,j);
            }
        cout << SusLineDP::solve() << endl;
    }

    return 0;
}