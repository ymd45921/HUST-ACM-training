/**
 *
 * 我是大憨批
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>

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

uint n, k;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> n >> k;
    auto xx = n * (n + 1) / 2, yy = xx % n;
    cerr << "sum = " << xx << "; mod = " << yy << endl;
    if (yy != k) cout << -1 << endl;
    else if (n & 1u)
    {
        cout << n;
        auto half = n / 2;
        for (int i = 1; i <= half; ++ i)
            cout << ' ' << i << ' ' << n - i;
        cout << endl;
    }
    else
    {
        assert(yy == n / 2);
        auto half = n / 2;
        cout << n << ' ' << half;
        for (int i = 1; i < half; ++ i)
            cout << ' ' << i << ' ' << n - i;
        cout << endl;
    }

    return 0;
}