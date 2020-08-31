/**
 *
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

unordered_map<uint, uint> cnt;

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, x, a;
    cin >> t;
    while (t --)
    {
        cnt.clear();
        cin >> n >> x;
        for (int i = 0; i < n; ++ i)
            cin >> a, ++ cnt[a];
        int v = 0, m = 1 + x;
        while (m --)
            while (++ v) if (!cnt[v]) break;
        cout << v - 1 << endl;
    }

    return 0;
}