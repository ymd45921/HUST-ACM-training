/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iomanip>

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

const int N = 250;
int a[N][N], sc[N][N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, m;
    cin >> t;
    cout << fixed << setprecision(8);
    while (t --)
    {
        cin >> n >> m;
        for (int i = 0; i < n; ++ i)
            for (int j = 0; j < m; ++ j)
                cin >> a[i][j], sc[i][j] = a[i][j];
        for (int j = 0; j < n; ++ j)
            for (int i = 1; i < m; ++ i)
                sc[i][j] += sc[i - 1][j];
        long double ans = 1.0;
        for (int j = 0; j < n; ++ j)
            for (int i = 1; i < m; ++ i)
                ans = max(ans, (long double)sc[i][j] / a[i][j]);
        cout << ans << endl;
    }

    return 0;
}