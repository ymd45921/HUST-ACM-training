/**
 *
 * 不是大小搭配！令 f(n) = 1 << n
 * 则 f(n) = sum<x:1~(n-1)>f(x) + 1
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

longs solution(uint n)
{
   auto half = n / 2;
   auto big = 1u << n, small = 0u;
   for (uint i = 1; i < half; ++ i)
       big |= 1u << i;
   for (uint i = half; i < n; ++ i)
       small |= 1u << i;
   return big - small;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, t;
    cin >> t;
    while (t --)
    {
        cin >> n;
        cout << solution(n) << endl;
    }
    
    return 0;
}