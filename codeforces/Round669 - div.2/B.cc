/**
 *
 * 因为数据范围不大，所以直接暴力就可以了
 * wdnmd
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <functional>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1060;
int a[N], t, n, b[N];
bitset<N> flag;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    cin >> t;
    while (t --)
    {
        cin >> n; flag.reset();
        for (int i = 0; i < n; ++ i)
            cin >> a[i];
        sort(a, a + n, greater<>());
        int now = b[0] = a[0], index = 1;
        flag[0] = true;
        for (int i = 1; i < n; ++ i)
        {
            auto xx = -1;
            for (int j = 1; j < n; ++ j)
            {
                if (flag[j]) continue;
                auto tmp = __gcd(now, a[j]);
                if (tmp > xx) index = j, xx = tmp;
            }
            flag[index] = true;
            b[i] = a[index], now = xx;
        }
        for (int i = 0; i < n; ++ i)
            cout << b[i] << ' ';
        cout << endl;
    }

    return 0;
}