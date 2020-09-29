/**
 *
 * ++ -- 又不分，真不愧是你
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

#define nextInt nexT<int>
#define nextLongs nexT<longs>
#define next128 nexT<__int128>

template<class T>
inline T nexT()
{
    T x = 0; int f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

#define ask(l, r) (cout << "? " << l << ' ' << r << endl), cin

int sum1[1060];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, sum23;
    cin >> n;
    ask(2, 3) >> sum23;
    for (int i = 2; i <= n; ++ i)
        ask(1, i) >> sum1[i];
    for (int i = n; i > 2; -- i)
        sum1[i] -= sum1[i - 1];
    sum1[1] = sum1[2] - (sum23 - sum1[3]);
    sum1[2] = sum23 - sum1[3];
    cout << "! ";
    for (int i = 1; i < n; ++ i)
        cout << sum1[i] << ' ';
    cout << sum1[n] << endl;

    return 0;
}

