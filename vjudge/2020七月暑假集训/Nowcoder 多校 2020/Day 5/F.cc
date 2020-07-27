/**
 *
 * 运行错误，服了
 * 运行错误完事了还能 WA，服了
 * 
 * 哦 di 会爆 int，那没事了
 * 毕竟这个题目也不是我从头开始读的
 * 以后需要注意这一点
 * 毕竟心急上头从来都不会有什么好结果
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

longs a[105];

int main()
{
    longs n, m = 0;
    cin >> n;
    for (int _ = 0; _ < n; ++ _)
        cin >> a[_], m = max(m, a[_]);
    for (int _ = 0; _ < n; ++ _)
    {
        auto i = a[_];
        longs d = 0, ii = 50 * i;
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