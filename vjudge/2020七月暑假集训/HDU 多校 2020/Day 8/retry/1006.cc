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

section intersection(int i, int j, int k)
{
    auto &ii = seq[i], &jj = seq[j];
    section sec = {max(ii.l, jj.l - k), min(ii.r, jj.r + k)};
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
        for (int i = 1; i < n; ++ i)
            seq[i + 1] = intersection(i + 1, i, k);
        for (int i = n; i > 1; -- i)
            seq[i - 1] = intersection(i - 1, i, k);
        for (int i = 1; i <= n; ++ i)
            if (isEmpty(seq[i])) {ok = false; break;}
            else ans.push_back(seq[i].l);
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