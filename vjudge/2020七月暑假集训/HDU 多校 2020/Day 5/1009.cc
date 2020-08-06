/**
 *
 * 折纸：横向 x 次，纵向 y 次；然后横纵裁剪
 * 得到碎片数：(2^x + 1) * (2^y + 1)
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

inline longs nextLongs()
{
    int f = 0, ch = getchar(); longs x = 0;
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const longs N = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    auto t = nextInt();
    while (t --)
    {
        auto n = nextLongs();
    }

    return 0;
}