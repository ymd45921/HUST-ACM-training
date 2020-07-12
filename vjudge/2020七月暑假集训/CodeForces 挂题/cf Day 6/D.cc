/**
 *
 * 贪，就嗯贪
 * 不过 rapid 本质是一个加速度一样的东西
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
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

vector<int> ans;

void solution(int n)
{
    auto res = n - 1, rapid = 1;
    while (res > rapid * 4)
    {
        res -= rapid * 2;
        ans.push_back(rapid);
        rapid += rapid;
    }
    if (res <= rapid * 2)
        ans.push_back(res - rapid);
    else
    {
        auto xx = res - rapid * 2;
        ans.push_back(xx / 2);
        ans.push_back(xx % 2);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, t; cin >> t;
    while (t --)
    {
        cin >> n;
        solution(n);
        cout << ans.size() << endl;
        for (auto &i : ans) cout << i << ' ';
        cout << endl;
        ans.clear();
    }

    return 0;
}