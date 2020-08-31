/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>

#if 0
#define log(x...) fprintf(stderr, x)
#endif

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

const int N = 410000;
int tr[N], p[N], ans[N], nxt[N];

auto fulfill = [](uint st, uint ed, bool dir)
{ while (st < ed) dir ? (nxt[ed] = st) : (nxt[st] = ed), ++st , -- ed, dir = !dir;};

void fillNext(uint cols)
{
    auto st = 0u, ed = cols - 1;
    fulfill(st, ed, true);
    ed = (st + ed) >> 1u;
    while (st < ed)
    {
        fulfill(st, ed, false);
        auto half = ((st + ed) >> 1u) - st + 1;
        st = ed + 1, ed = ed + half;
    }
    (cols > 1 ? nxt[cols - 2] : nxt[0]) = -1;
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), k = nextInt();
        const auto cols = 1u << (uint)k, rows = 2u * n;
        const auto len = (int)rows * (int)cols;
        fillNext(cols);
#ifdef log
        int $now = (int)cols - 1;
        while ($now != -1) log("%d ", $now), $now = nxt[$now];
        log("\n");
#endif
        for (int i = 1; i <= len; ++ i) p[i] = nextInt();
        const auto per = [&](uint x, uint y) -> int& {return tr[x * cols + y + 1];};
        auto pen = len; auto yy = cols - 1;
        while (pen)
        {
            if (yy & 1u || cols & 1u) for (int i = 0; i < rows; ++ i)
                per(rows - 1 - i, yy) = pen - i;
            else for (int i = 0; i < rows; ++ i)
                per(i, yy) = pen - i;
            pen -= rows, yy = nxt[yy];
        }
        for (int i = 1; i <= len; ++ i) ans[i] = p[tr[i]];
        for (int i = 1; i < len; ++ i) printf("%d ", ans[i]);
        printf("%d\n", ans[len]);
    }

    return 0;
}