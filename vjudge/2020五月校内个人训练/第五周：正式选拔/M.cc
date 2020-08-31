/**
 *
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

int check(int x, int y)
{
    if (x == y) return x == 1 ? 1 : -1;
    if (x > y) swap(x, y);
    int cnt = (y - x) / x;
    int yy = y - cnt * x;
    if (yy > x) yy -= x, ++ cnt;
    auto res = check(yy, x);
    return res == -1 ? -1 : res + cnt;
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, x, y;
    cin >> t;
    while (t --)
    {
        cin >> x >> y;
        cout << check(x, y) << endl;
    }

    return 0;
}