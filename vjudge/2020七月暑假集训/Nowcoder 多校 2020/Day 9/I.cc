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
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 5;
int cnt[10];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        memset(cnt, 0, sizeof cnt);
        int n = nextInt(), xx = 0, yy = 0;
        while (n --) ++ cnt[nextInt()];
        for (int i = 1; i < 10; ++ i)
            if (cnt[i]) {-- cnt[i], xx = i; break;}
        for (int i = 1; i < 10; ++ i)
            if (cnt[i]) {-- cnt[i], yy = i; break;}
        string s;
        s.append(1, yy + '0');
        s.append(cnt[0], '0');
        for (int i = 1; i < 10; ++ i)
            s.append(cnt[i], i + '0');
        int top = 0, len = s.length();
        while (-- len >= 0)
        {
            auto _this = s[len] - '0';
            auto _tmp = _this * xx + top;
            top = _tmp / 10;
            s[len] = _tmp % 10 + '0';
        }
        if (top) printf("%d", top);
        printf("%s\n", s.c_str());
    }

    return 0;
}