/**
 *
 * sac 读 cerr
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

char map[105][105];
int n;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> map[i];

    int maxlength = 0, ll = -1, rr = -1, ff = -1;
    for (int j = 0; j < n; ++ j)
    {
        int f = -1, l = -1;
        for (int i = 0; i < n; ++ i)
            if (map[i][j] == '1')
                !~f ? f = l = i : l = i;
        maxlength = max(maxlength, l - f + 1);
        if (~f) !~ll ? (ll = rr = j, ff = f) : rr = j;
    }
    int x = (maxlength - 3) / 2;
    if (ll == rr) { cout << 1 << endl; return 0; }
    cerr << x << ": (" << ff << ", " << ll << ")\n";
    struct {int x, y;} p[] =
            {
                    {ff, ll}, {ff, ll + x + 1},
                    {ff + x + 1, ll}, {ff + x + 1, ll + x + 1},
                    {ff + 2 * x + 2, ll}, {ff + 2 * x + 2, ll + x + 1}
            };
    bool edge[] =
            {
                map[p[0].x][p[0].y + 1] == '1',
                map[p[0].x + 1][p[0].y] == '1',
                map[p[1].x + 1][p[1].y] == '1',
                map[p[2].x][p[2].y + 1] == '1',
                map[p[2].x + 1][p[2].y] == '1',
                map[p[3].x + 1][p[3].y] == '1',
                map[p[4].x][p[4].y + 1] == '1',
            };
    int hasEdge = 0;
    for (bool i : edge) hasEdge += i;
    if (hasEdge == 7) cout << 8 << endl;
    else if (hasEdge == 6)
    {
        if (!edge[3]) cout << 0 << endl;
        else if (!edge[2]) cout << 6 << endl;
        else if (!edge[4]) cout << 9 << endl;
    }
    else if (hasEdge == 5)
    {
        if (!edge[1] && !edge[5]) cout << 2 << endl;
        else if (!edge[2] && !edge[4]) cout << 5 << endl;
        else if (!edge[1] && !edge[4]) cout << 3 << endl;
    }
    else if (hasEdge == 4) cout << 4 << endl;
    else if (hasEdge == 3) cout << 7 << endl;
    else cout << 1 << endl;

    return 0;
}