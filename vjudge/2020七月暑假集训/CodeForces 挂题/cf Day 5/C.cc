/**
 *
 * 每块蛋糕都放在盘子上，意思是
 * 每种蛋糕至少有一个盘子盛放
 *
 * 语文题
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <unordered_map>

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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    unordered_map<uint, int> cnt;
    int x, m = 3;
    while (m --)
    {
        cin >> x;
        ++ cnt[x];
    }

    if (cnt[1]
        || cnt[2] >= 2
        || cnt[3] >= 3
        || (cnt[4] >= 2
        && cnt[2]))
        cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}