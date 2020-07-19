/**
 *
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

const int N = 2e6 + 5;
char s[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int q, off = 0, pos;
    char ch;
    cin >> s >> q;
    auto len = strlen(s);
    while (q --)
    {
        cin >> ch >> pos;
        if (ch == 'M')
        {
            off += pos;
            while (off >= len) off %= len;
            while (off <= -len) off += (-off) / len * len;
        }
        else
        {
            auto xx = pos + off - 1;
            while (xx < 0) xx += (-xx) / len * len + len;
            while (xx >= len) xx %= len;
            cout << s[xx] << endl;
        }
    }

    return 0;
}