/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>

#define CountDown(I, T) for (auto I = T; I; -- I)
#define l first
#define r second

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

using section = pair<longs, longs>;
vector<section> seq;
vector<longs> ans;

section intersection(int i, int k)
{
    auto &pre = seq[i - 1], &nex = seq[i + 1], &now = seq[i];
    auto last = ans[i - 1];
    section sec = {max(now.l, nex.l - k), min(now.r, nex.r + k)};
    if (i - 1 != 0) sec = {max(sec.l, last - k), min(sec.r, last + k)};
    return sec;
}

bool isEmpty(section &ii) {return ii.l > ii.r;}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        longs n = nextInt(), k = nextInt();
        seq.clear(), seq.emplace_back(0, 1e9);
        ans.clear(), ans.push_back(0);
        CountDown(i, n)
        {
            int l = nextInt(), r = nextInt();
            seq.emplace_back(l, r);
        }
        seq.emplace_back(0, 1e9);
        bool ok = true;
        for (int i = 1; i <= n; ++ i)
        {
            auto res = intersection(i, k);
            if (isEmpty(res)) {ok = false; break;}
            ans.push_back((res.l + res.r) / 2);
        }
        if (ok)
        {
            puts("YES");
            for (int i = 1; i < n; ++ i)
                printf("%lld ", ans[i]);
            printf("%lld\n", ans[n]);
        }
        else puts("NO");
    }

    return 0;
}