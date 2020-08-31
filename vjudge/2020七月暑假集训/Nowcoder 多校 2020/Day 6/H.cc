/**
 *
 * 你已经通过 https://loj.ac/problem/10165 板子题了
 * 那么就说明你已经学会了数位 DP 了！
 * 试一试↓↓
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <vector>
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

vector<int> dim;
constexpr longs mod = 1e9 + 7;

longs dfs(uint x, int delta, bool upto, bool down)
{
    if (!x) return 1;
    if ()
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    string n;
    cin >> n;
    auto pos = n.rend();
    dim.push_back(-1);
    for (auto i = n.rbegin(); i != pos; ++ i)
        dim.push_back(*i - '0');


    return 0;
}