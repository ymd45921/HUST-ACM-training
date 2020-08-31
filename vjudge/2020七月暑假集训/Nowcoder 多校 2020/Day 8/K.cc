/**
 * long long 出错…… 虽然不止这一个问题
 * 它甚至爆了 long long）
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <deque>

#define log(x ...) fprintf(stderr, x)

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

void println(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]); putchar('\n');
}

const int N = 1e5 + 5;
int a[N], b[N], c[N];
longs sum[N];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    deque<pair<__int128, longs>> contrib;
    for (int cases = 1; cases <= t; ++ cases)
    {
        int n = nextInt(), selected = 0; contrib.clear();
        for (int i = 1; i <= n; ++ i) sum[i] = a[i] = nextInt();
        for (int i = 1; i <= n; ++ i) c[i] = b[i] = nextInt();
        for (int i = 2; i <= n; ++ i)
            sum[i] += sum[i - 1], c[i] = min(c[i - 1], c[i]);
        for (int i = n; i; -- i)
        {
            if (sum[i] < sum[1]) continue;
            auto chance = c[i] - selected;
            while (!contrib.empty() && contrib.front().first <= sum[i])
                chance += contrib.front().second,
                        selected -= contrib.front().second,
                        contrib.pop_front();
            contrib.emplace_front(sum[i], chance);
            selected += chance;
        }
        assert(selected == b[1]);
        __int128 ans = 0;
        while (!contrib.empty())
            ans += contrib.front().first * contrib.front().second,
                    contrib.pop_front();
        printf("Case #%d: %d ", cases, b[1]);
        println(ans);
    }

    return 0;
}