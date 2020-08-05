/**
 *
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
#include <unordered_map>
#include <cmath>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const double pi = 3.1415926535897932384626;

template <typename number>
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
template <typename number>
int compareTo(number a, number b) {return compareTo(a-b);}

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

const int N = 100;
unordered_map<double, int> xx, yy, zz;
struct triple{double x, y, z;} pts[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    unsigned t, n; double x, y, z;
    using cnt = unordered_map<double, int>;
    auto centre = [&](cnt &x, cnt &y)
    {
        double xxx = 0, yyy = 0;
        for (auto &i : x) xxx += i.first;
        for (auto &i : y) yyy += i.first;
        auto cc = n << 1u;
        return make_pair(xxx / cc, yyy / cc);
    };


    cin >> t;
    while (t --)
    {
        xx.clear(), yy.clear(), zz.clear();
        cin >> n; auto lim = n << 1u;
        while (lim --)
        {
            cin >> x >> y >> z;
            pts[lim] = {x, y, z};
            ++ xx[x], ++ yy[y], ++ zz[z];
        }
        long double ans = 0;
        if (zz.size() == 2)
        {
            auto xy = centre(xx, yy);
            auto vec = make_pair(xy.first - pts[0].x, xy.second - pts[0].y);
            auto rad = pi * (vec.first * vec.first + vec.second * vec.second);
            double h1 = 0, h2 = 0; int cnt = 0;
            for (auto & ii : zz) (cnt ++ ? h2 : h1) = ii.first;
            auto height = abs(h2 - h1);
            ans = rad * height;
        }
        else if (yy.size() == 2)
        {
            auto xz = centre(xx, zz);
            auto vec = make_pair(xz.first - pts[0].x, xz.second - pts[0].z);
            auto rad = pi * (vec.first * vec.first + vec.second * vec.second);
            double h1 = 0, h2 = 0; int cnt = 0;
            for (auto & ii : yy) (cnt ++ ? h2 : h1) = ii.first;
            auto height = abs(h2 - h1);
            ans = rad * height;
        }
        else
        {
            auto yz = centre(yy, zz);
            auto vec = make_pair(yz.first - pts[0].y, yz.second - pts[0].z);
            auto rad = pi * (vec.first * vec.first + vec.second * vec.second);
            double h1 = 0, h2 = 0; int cnt = 0;
            for (auto & ii : xx) (cnt ++ ? h2 : h1) = ii.first;
            auto height = abs(h2 - h1);
            ans = rad * height;
        }
        cout << fixed << setprecision(6) << ans << endl;
    }

    return 0;
}