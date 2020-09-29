/**
 *
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <bitset>
#include <cstring>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace In
{
    template <class T>
    inline void read(T &x)
    {
        x = 0;
        int ch = getchar(), f = 1;
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        x = f ? -x : x;
    }

    template <class T, class... Ts>
    inline void read(T &x, Ts &... y)
    {return read(x), read(y...);}
}

int f[][10] =
{
        {1, 0},
        {2, 1, 9},
        {0},
        {0},
        {2, 2, 8},
        {1, 5},
        {2, 4, 6},
        {0},
        {0},
        {2, 3, 7}
}, siz, lim;
string s, ans;
bitset<10> can[10][10];
#define CHAR(n) char('0' + n)
#define NUM(n) int(n - '0')
#define CNT(n) f[n][0]

bool go(int pos);

auto divide(int a, int b)
{
    return can[b][a];
}

bool test(int now, int pos)
{
    if (now == -1) return false;
    if (CNT(now))
    {
        auto cnt = CNT(now), ii = 1;
        while (ii <= cnt)
        {
            ans.push_back(CHAR(f[now][ii]));
            auto res = go(pos + 1);
            if (res) return true;
            else
            {
                ans.pop_back();
                ++ ii;
            }
        }
        return false;
    }
    else return false;
}

bool go(int pos)
{
    if (pos == lim)
    {
        bool check = true;
        for (int ii = lim; ii < siz; ++ ii)
        {
            auto xx = 0;
            for (int i = 1; i <= ii; ++ i)
            {
                auto j = ii - i;
                if (i >= lim || j >= lim) continue;
                xx += NUM(ans[i]) * NUM(ans[j]);
            }
            check &= CHAR(xx % 10) == s[ii];
            if (!check) return false;
        }
        return check;
    }
    auto now = NUM(s[pos]);
    bitset<10> todo;
    if (pos)
    {
        int ll = 1, rr = pos - 1;
        while (ll <= rr)
        {
            auto x = 2 - int(ll == rr);
            now -= x * NUM(ans[ll]) * NUM(ans[rr]);
            ++ ll, -- rr;
        }
        while (now < 0) now += 10;
        if (now % 2) return false;
        todo |= divide(now / 2, NUM(ans[0]));
        auto xx = divide(now, NUM(ans[0]));
        for (int i = 0; i < 10; i += 2)
            if (xx[i]) todo[i / 2] = true;
    }
    else todo[now] = true;
    bool res = false;
    for (int i = 0; i < 10; ++ i)
        if (todo[i])
        {
            res |= test(i, pos);
            if (res) break;
        }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    for (int i = 0; i < 10; ++ i)
    {
        int j = 0, ii;
        while (j < 10 && !can[i][ii = (i * j) % 10][j])
            can[i][ii][j] = true, ++ j;
    }
    cin >> s;
    reverse(s.begin(), s.end());
    siz = s.length();
    lim = (siz + 1) / 2;
    auto ok = siz % 2 != 0 && go(0);
    reverse(ans.begin(), ans.end());
    if (!ok) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
}

