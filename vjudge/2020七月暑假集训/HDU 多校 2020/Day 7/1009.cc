/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <deque>

#define CEIL(a, b) ((a) / (b) + bool((a) % (b)))

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

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), x = nextInt(), y = nextInt();
        if ((x + y > n + 1) ||
            (x == 1 && y != n) ||
            (x != n && y == 1))
        {printf("NO\n"); continue;}
        deque<int> ans;
        auto nn = n, yy = y, xy = n - x - y + 1;
        while (yy --) ans.push_back(nn --);
        if (y - 1 && CEIL(xy, y - 1) > x - 1)
        {printf("NO\n"); continue;}
        while (nn)
        {
            auto todo = y - 1;
            if (xy < y - 1) todo = xy, xy = 0;
            else xy -= todo;
            for (auto ii = nn - todo; ii <= nn; ++ ii)
                ans.push_front(ii);
            nn = nn - todo - 1;
        }
        puts("YES");
        printf("%d", ans.front()), ans.pop_front();
        while (!ans.empty())
            printf(" %d", ans.front()), ans.pop_front();
        puts("");
    }

    return 0;
}