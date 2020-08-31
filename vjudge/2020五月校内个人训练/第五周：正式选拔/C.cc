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
#include <cmath>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#define number longs
struct point
{
    number x, y;

    point() = default;
    point(number x, number y) : x(x), y(y) {}

    point operator +(const point &rhs) const {return {x + rhs.x, y + rhs.y};}
    point operator -(const point &rhs) const {return {x - rhs.x, y - rhs.y};}
    number operator *(const point &rhs) const {return x * rhs.x + y * rhs.y;}
    point operator *(const number rhs) const {return {rhs * x, rhs * y};}
    point operator /(const number rhs) const {return {x / rhs, y / rhs};}
    point &operator +=(const point& rhs) {x += rhs.x; y += rhs.y; return *this;}
    point &operator -=(const point& rhs) {x -= rhs.x; y -= rhs.y; return *this;}
    point &operator *=(const number rhs) {x *= rhs; y *= rhs; return *this;}
    point &operator /=(const number rhs) {x /= rhs; y /= rhs; return *this;}
    bool operator ==(const point &rhs) const {return x == rhs.x && y == rhs.y;}
    bool operator !=(const point &rhs) const {return !(rhs == *this);}

    number dot(const point &rhs) const {return x * rhs.x + y * rhs.y;}
    number cross(const point &rhs) const {return rhs.y * x - rhs.x * y;}
    number length() const {return sqrt(dot(*this));}
    number distance(const point &b) const {return (*this - b).length();}
    number distance(const point &ls, const point &rs) const
    {return fabs((ls - *this).cross(rs - *this)) / ls.distance(rs);}
    point normal() {return (x || y) ? *this / length() : point(0, 0);}
    number angle() const {return atan2(y, x);}
    point rotate(number a) const
    {number c = cos(a), s = sin(a); return {c * x - s * y, s * x + c * y};}
    point perpendicular() const {return {-y, x};}
    point symmetry() const {return {-x, -y};}

    bool operator<(const point& rhs) const
    {
        return x != rhs.x ? x < rhs.x : y > rhs.y;
    }
};

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

const int N = 2e5 + 5;
longs n, r, x, y;
point hls[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    cin >> n >> r;
    if (!n)
    {
        cout << 0 << endl;
        return 0;
    }
    for (int i = 0; i < n; ++ i)
    {
        cin >> x >> y;
        int step = sqrt(r * r - y * y);
        hls[i].x = x - step;
        hls[i].y = x + step;
    }
    sort(hls, hls + n);
    longs ans = 1, ll = -1, rr = 1e6 + 7;
    for (int i = 0; i < n; ++ i)
    {
        auto &now = hls[i];
        ll = max(ll, now.x);
        rr = min(rr, now.y);
        if (ll > rr)
        {
            ++ ans;
            ll = now.x;
            rr = now.y;
        }
    }
    cout << ans << endl;


    return 0;
}