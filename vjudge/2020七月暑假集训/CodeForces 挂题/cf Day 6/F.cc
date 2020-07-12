/**
 *
 * 构造一组答案：排序所有区间，记录使用状况
 * 问题在于如何判定唯一，并且输出可能的第二种解
 *
 * 方法一：使用另一种方法构造出第二个解进行比较
 *
 * 方法二：使用线段树维护
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

struct range
{
    uint ll, rr, id;

    bool operator<(const range &rhs) const
    { return rr == rhs.rr ? ll < rhs.ll : rr < rhs.rr; }
};

auto comparer = [](const range &lhs, const range &rhs)
{ return lhs.ll == rhs.ll ? lhs.rr < rhs.rr : lhs.ll < rhs.ll; };

const int N = 2e5 + 5;
range f[N];
uint ans$1[N], ans$2[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    uint n; cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> f[i].ll >> f[i].rr, f[i].id = i;
    memset(ans$1, -1, sizeof(ans$1));
    memset(ans$2, -1, sizeof(ans$2));
    sort(f + 1, f + n + 1);
    for (int i = 1; i <= n; ++ i)
    {
        
    }

    return 0;
}