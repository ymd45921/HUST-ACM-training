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

char s[1050];
int cnt[26];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        memset(cnt, 0, sizeof cnt);
        for (int i = 1; i <= n; ++ i)
        {
            scanf("%s", s);
            auto len = strlen(s);
            for (int j = 0; j < len; ++ j)
                ++ cnt[s[j] - 'a'];
        }
        bool ok = true;
        for (auto ii : cnt)
            (ii % n) && (ok &= false);
        printf(ok ? "YES\n" : "NO\n");
    }

    return 0;
}