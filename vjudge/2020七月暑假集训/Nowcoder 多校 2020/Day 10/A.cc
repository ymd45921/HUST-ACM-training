/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <bitset>
#include <algorithm>
#include <cstring>
#include <vector>

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

const int N = 1e6 + 5;
bitset<N> tag;
vector<int> ans;

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int p = nextInt(), now = 1, res = p - 2;
        tag.reset(), ans.clear();
        tag[1] = true, ans.push_back(1);
//        while (res --)
//            if (!tag[now * 2 % p])
//                tag[now * 2 % p] = true,
//                ans.push_back(now * 2 % p),
//                now = now * 2 % p;
//            else if (!tag[now * 3 % p])
//                tag[now * 3 % p] = true,
//                ans.push_back(now * 3 % p),
//                now = now * 3 % p;
//            else {tag[0] = true; break;}
        if ((p - 1) % 2 == 0)
            while (res --)
                now = now * 2 % p,
                tag[now] = true, ans.push_back(now);
        else if ((p - 1) % 3 == 0)
            while (res --)
                now = now * 3 % p,
                tag[now] = true, ans.push_back(now);
        else tag[0] = true;
        if (tag[0]) printf("-1");
        else for (auto &ii : ans) printf("%d ", ii);
        puts("");
    }

    return 0;
}