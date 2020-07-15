/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

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

inline longs gcd(longs a, longs b)
{
    if (a < b) gcd(b, a);
    if (!b) return a;
    else return gcd(b, a % b);
}

inline longs lcm(longs a, longs b)
{ return a * b / gcd(a, b); }

const int N = 5050;
int mat[N][N];

namespace STtable2D_simple
{
    int log[N], high[N][N];
    uint _log;
    int row, col, sq, _max;

    template <class T> T max4(T t1, T t2, T t3, T t4)
    { return max(max(t1, t2), max(t3, t4)); }

    auto import = []
    {
        for (int i = 1; i <= row; ++ i)
            for (int j = 1; j <= col; ++ j)
                high[i][j] = mat[i][j];
        _log = log[sq];
    };

    void init(uint k)
    {
        log[0] = -1;
        for (uint i = 1; i <= k; ++ i)
            log[i] = log[i >> 1u] + 1;
        memset(high, 0x80, sizeof(high));
        import();
    }

    void make(uint a, uint b)
    {
        for (uint p = 0; p < _log; ++ p)
            for (int i = 1; i + (1u << p) <= a; ++ i)
                for (int j = 1; j + (1u << p) <= b; ++ j)
                    high[i][j] = max4<int>(
                            high[i][j],
                            high[i + (1u << p)][j + (1u << p)],
                            high[i + (1u << p)][j],
                            high[i][j + (1u << p)]
                    );
    }

    void query(int x, int y)
    {
        _max = max4<int>(
                high[x][y],
                high[x + sq - (1u << _log)][y + sq - (1u << _log)],
                high[x][y + sq - (1u << _log)],
                high[x + sq - (1u << _log)][y]
        );
    }

    auto solve(int n, int m, int k)
    {
        row = n, col = m, sq = k;
        init(k); make(n, m);
        longs ans = 0;
        const int $row = n - k + 1, $col = m - k + 1;
        for (int i = 1; i <= $row; ++ i)
            for (int j = 1; j <= $col; ++ j)
                query(i, j), ans += _max;
        return ans;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            mat[i][j] = lcm(i, j);
    auto xx = STtable2D_simple::solve(n, m, k);
    cout << xx << endl;

    return 0;
}