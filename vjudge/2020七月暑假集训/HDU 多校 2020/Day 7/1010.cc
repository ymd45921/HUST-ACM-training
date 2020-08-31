#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;
using longs = long long;
using uint = unsigned;

inline longs nextLongs()
{
    int f = 0, ch = getchar(); longs x = 0;
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

longs gcd(longs a, longs b)
{
    if (a < b) swap(a, b);
    if (!b) return a;
    else return gcd(b, a % b);
}

const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

pair<longs, longs> bfs(longs x, longs y)
{
    queue<pair<longs, longs>> que;
    unordered_map<longs, unordered_map<longs, int>> tag;
    const static auto search = [&](longs x, longs y)
    {
        tag[x][y] = 1;
        for (int i = 0; i < 8; ++ i)
        {
            auto xx = x + dx[i], yy = y + dy[i];
            if (xx == yy && xx != 1) return true;
            if (gcd(xx, yy) > 1) ++ tag[x][y];
            else continue;
            if (tag[xx][yy]) continue;
            tag[xx][yy] = 1;
            que.push(make_pair(xx, yy));
        }
        return false;
    };
    que.push(make_pair(x, y));
    bool infinity = (x == y) && (x != 1);
    longs denominator = 0;
    while (!que.empty())
    {
        auto top = que.front();
        que.pop();
        infinity |= search(top.first, top.second);
        if (infinity) break;
        denominator += tag[top.first][top.second];
    }
    if (infinity) return {0, 1};
    else return {tag[x][y], denominator};
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextLongs();
    while (t --)
    {
        auto x = nextLongs(), y = nextLongs();
        if (gcd(x, y) == 1) puts("0/1");
        auto res = bfs(x, y);
        auto reduce = gcd(res.first, res.second);
        res.first /= reduce, res.second /= reduce;
        printf("%lld/%lld\n", res.first, res.second);
    }

    return 0;
}