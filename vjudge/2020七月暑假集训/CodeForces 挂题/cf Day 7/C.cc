/**
 *
 * 并不算麻烦的构造
 *
 * WA 原因是 long long，会在 #6 挂掉
 * 还是看了题解才知道的，操（
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

const int N = 1e5 + 5;
int l[N], p[N], b[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, m, sum = 0;            // sum 会爆 int
    cin >> n >> m;
    for (int i = 1; i <= m; ++ i)
        cin >> l[i], sum += l[i];
    if (sum < n) {cout << -1 << endl; return 0;}
    int bound = 0;
    for (int i = 1; i <= m; ++ i)
    {
        p[i] = i; b[i] = i + l[i];
        bound = max(bound, b[i]);
    }
    int x = m + 1; p[m + 1] = n + 1;
    if (bound > n + 1) {cout << -1 << endl; return 0;}
    else if (bound <= n) do
    {
        -- x;
        b[x] = p[x + 1];
        p[x] = b[x] - l[x];
    } while (b[x - 1] < p[x]);
    for (int i = 1; i <= m; ++ i) cout << p[i] << ' ';
    cout << endl;

    return 0;
}