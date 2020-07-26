/**
 *
 * 运行错误，服了
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>

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

int a[105];

int main()
{
    int n, m = 0;
    cin >> n;
    for (int _ = 0; _ < n; ++ _)
        cin >> a[_], m = max(m, a[_]);
    for (int _ = 0; _ < n; ++ _)
    {
        auto i = a[_];
        int d = 0, ii = 50 * i;
        if (i) d = ii / m + (bool)(ii % m);
        printf("+");
        for (int iii = 0; iii < d; ++ iii) putchar('-');
        puts("+");
        putchar('|');
        for (int iii = 1; iii < d; ++ iii) putchar(' ');
        if (i) putchar(i == m ? '*' : ' ');
        printf("|%d\n", i);
        printf("+");
        for (int iii = 0; iii < d; ++ iii) putchar('-');
        puts("+");
    }

    return 0;
}