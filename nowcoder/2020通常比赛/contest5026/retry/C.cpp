/**
 *
 *
 */
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <cstring>
#include <map>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 2e6+5;
const int inf = 0x7fffffff;
const longs INF = 0x7fffffffffffffff;
const double eps = 1e-8;

int max4(int a, int b, int c, int d)
{
    return max(a,max(b,max(c,d)));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int na, nb, nc, nd, m;
    int x, y, p[13];
    for (int i = 0; i <= 12; ++ i) p[i] = i;
    function<int(int)> father = [&](int ii) -> int
    {
        if (p[ii] == ii) return ii;
        else return p[ii] = father(p[ii]);
    };
    auto join = [&](int x, int y)
    {
        int px = father(x), py = father(y);
        p[px] = py;
    };
    int num[13], cnt = 0, ans = 0;
    map<int,int> mm; int f[13][13][13][13][13];

    auto dp = [&]
    {
        memset(f, 0, sizeof(f)); f[0][0][0][0][0] = 1;
        for (int i = 1; i <= cnt; ++ i)
            for (int a = 0; a <= na; ++ a)
                for (int b = 0; b <= nb; ++ b)
                    for (int c = 0; c <= nc; ++ c)
                        for (int d = 0; d <= nd; ++ d)
                        {
                            auto &xx = num[i];
                            if (a + xx <= na) f[i][a+xx][b][c][d] += f[i-1][a][b][c][d];
                            if (b + xx <= nb) f[i][a][b+xx][c][d] += f[i-1][a][b][c][d];
                            if (c + xx <= nc) f[i][a][b][c+xx][d] += f[i-1][a][b][c][d];
                            if (d + xx <= nd) f[i][a][b][c][d+xx] += f[i-1][a][b][c][d];
                        }
        return f[cnt][na][nb][nc][nd];
    };

    cin >> na >> nb >> nc >> nd >> m;
    while (m --)
    {
        cin >> x >> y;
        join(x,y);
    }
    memset(num,0,sizeof num);
    for (int i = 1; i <= 12; ++ i)
    {
        if (!mm[father(i)])
            mm[p[i]] = ++cnt;
        ++ num[mm[p[i]]];
    }
    cout << dp() << endl;

    return 0;
}