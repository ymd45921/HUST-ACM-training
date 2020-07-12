/**
 *
 * 主要麻烦的就是策略：
 * - 相同时平均分配，可以缩短字符串长度
 * - 不相同时一条龙，可以降低最大字符串的字典序
 * 虽然但是，这确实是显然的（
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

const int N = 1e5 + 5;
char s[N];

void solution(int n, int k)
{
    sort(s, s + n);
    if (k == 1)
    {
        cout << s << endl;
        return;
    }
    if (s[0] != s[k - 1]) cout << s[k - 1] << endl;
    else
    {
        cout << s[0];
        if (s[k] != s[n - 1]) cout << s + k << endl;
        else
        {
            auto res = n - k;
            auto len = res / k + (res % k != 0);
            cout << string(len, s[k]) << endl;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t, n, k;
    cin >> t; while (t --)
    {
        cin >> n >> k >> s;
        solution(n, k);
    }

    return 0;
}