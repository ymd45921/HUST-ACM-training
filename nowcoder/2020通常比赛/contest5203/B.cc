/**
 *
 * 怎么还能WA
 * 
 * 改成滚动数组dp就行了
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

const int N = 1e5+5;
const int mod = 3600;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, n, a[N], cnt[3605];
    bool vis[2][3605];
    cin >> t;
    while (t --)
    {
        cin >> n; bool find = false;
        memset(cnt, 0, sizeof cnt);
        memset(vis, 0, sizeof vis);
        for (int i = 1; i <= n; ++ i)
        {
            cin >> a[i];
            a[i] %= mod;
            if (!a[i]) find = true;
            else ++cnt[a[i]];
        }
        if (find)
        {
            cout << "YES" << endl;
            continue;
        }
//        sort(a+1, a+1+n);
        int tag = 0;
        for (int i = 1; i < 3600; ++ i)
            if (!find)
                while (cnt[i] --)
                {
                    int ii = tag++ & 1;
                    if (vis[ii^1][3600 - i])
                    {
                        find = vis[ii][3600] = true;
                        break;
                    }
                    for (int x = 0; x <= mod; ++ x)
                        vis[ii][x] = vis[ii^1][x];
                    for (int j = i - 1; j; -- j)
                        if (vis[ii^1][mod + j - i]) vis[ii][j] = true;
                    for (int j = 3599; j > i; -- j)
                        if (vis[ii^1][j - i]) vis[ii][j] = true;
                    vis[ii][i] = true;
                }
        vis[0][mod] = vis[0][mod] || vis[0][0];
        vis[1][mod] = vis[1][mod] || vis[1][0];
        cout << (vis[0][mod] || vis[1][mod] ? "YES" : "NO") << endl;
    }


    return 0;
}