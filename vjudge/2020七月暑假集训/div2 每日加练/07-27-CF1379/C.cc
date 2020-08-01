/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

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

constexpr int M = 1e5 + 5;
vector<pair<int, int>> item;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, m, a, b;
    cin >> t;
    while (t --)
    {
        cin >> n >> m;
        item.clear();
        while (m --)
        {
            cin >> a >> b;
            item.emplace_back(a, b);
        }

    }

    return 0;
}