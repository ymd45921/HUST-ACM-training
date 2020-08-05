/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

template <class T> struct fraction
{
    T num, den;

    fraction() = default;
    fraction(T u, T v): num(u), den(v)
    { if (!v) num = 1; else if (v < 0) num = -u, den = -v; }

    constexpr static const long double $eps = 0;        // 这个 1e-8 反而过不了
    static int sgn(long double x) {return x < -$eps ? -1 : x > $eps;}
    static T gcd(T a, T b) {return a < b ? gcd(b, a) : (!b ? a : gcd(b, a % b));}

    auto toNumber() const { return (long double) num / den; }
    int compareTo(const fraction &rhs) const {return sgn(this->toNumber() - rhs.toNumber());}
    bool equals(const fraction &rhs) const {return den == 0 || rhs.den == 0 ? den == rhs.den : !compareTo(rhs);}
    fraction &reduce() { auto x = gcd(num, den); num /= x, den /= x; return *this;}

    bool operator ==(const fraction &rhs) const { return num * rhs.den == den * rhs.num;}
    bool operator <(const fraction &rhs) const {return den && (!rhs.den || compareTo(rhs) < 0);}
    fraction operator -() const {return {-num, den};}
};


namespace Geo
{
    using number = longs;
    const number eps = fraction<longs>::$eps;

    int compareTo(number x) {return x < -eps ? -1 : x > eps;}
    int compareTo(number a, number b) {return compareTo(a-b);}

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
        point normal() const {return (x || y) ? *this / length() : point(0, 0);}
        number angle() const {return atan2(y, x);}
        point rotate(number a) const
        {number c = cos(a), s = sin(a); return {c * x - s * y, s * x + c * y};}
        point perpendicular() const {return {-y, x};}
        point symmetry() const {return {-x, -y};}
        number square() const { return x * x + y * y; }
    };
}

using point = Geo::point;
using frac = fraction<longs>;

const int N = 2060;

point a[N];
vector<frac> li;

frac getSlope(const point &ll, const point &rr = {0, 0})
{
    auto ld = ll.square(), rd = rr.square();
    if (!ld) ld = 1; if (!rd) rd = 1;
    return {rr.y * ld - ll.y * rd, rr.x * ld - ll.x * rd};
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, ans = 1;
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> a[i].x >> a[i].y;
    for (int i = 0; i < n; ++ i)
    {
        frac tmp = getSlope(a[i]);
        for (int j = i + 1; j < n; ++ j)
        {
            frac ff = getSlope(a[i], a[j]);
            if (ff.equals(tmp)) continue;
            li.push_back(ff);
        }
        sort(li.begin(), li.end());
        auto len = li.size();
        for (int l = 0, r = 0; l < len;)
        {
            r = l;
            while (r < len && li[r].equals(li[l])) ++ r;
            ans = max(ans, r - l + 1ll);
            l = r;
        }
        li.clear(); // 不要忘记了！
    }
    cout << ans << endl;

    return 0;
}