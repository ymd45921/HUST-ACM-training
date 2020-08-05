#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
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
    using $$ = __int128;

    fraction() = default;
    fraction(T u, T v): num(u), den(v)
    { if (!v) num = 1; else if (v < 0) num = -u, den = -v; }

    constexpr static const long double $eps = 0;
    static int sgn(long double x) {return x < -$eps ? -1 : x > $eps;}
    static T gcd(T a, T b) {return a < b ? gcd(b, a) : (!b ? a : gcd(b, a % b));}

    auto toNumber() const { return (long double) num / den; }
    int compareTo(const fraction &rhs) const {return sgn(this->toNumber() - rhs.toNumber());}
    bool equals(const fraction &rhs) const {return den == 0 || rhs.den == 0 ? den == rhs.den : !compareTo(rhs);}
    fraction &reduce() { auto x = gcd(num, den); num /= x, den /= x; return *this;}
    auto atan2() const {return std::atan2(num, den);}
    fraction reciprocal() const {return {den, num};}

    bool operator ==(const fraction &rhs) const { return num * rhs.den == den * rhs.num;}
    bool operator <(const fraction &rhs) const {return den && (!rhs.den || ($$)num * rhs.den < ($$)den * rhs.num);} // 小心爆炸
    fraction operator -() const {return {-num, den};}
    fraction operator +(const fraction &rhs) const
    {auto x = gcd(den, rhs.den); return {rhs.den / x * num + den / x * rhs.num, den / x * rhs.den};}
    fraction operator -(const fraction &rhs) const
    {auto x = gcd(den, rhs.den); return {rhs.den / x * num - den / x * rhs.num, den / x * rhs.den};}
    fraction operator *(const fraction &rhs) const
    {auto $1 = gcd(abs(num), rhs.den), $2 = gcd(abs(rhs.num), den); return {num / $1 * (rhs.num / $2), den / $2 * (rhs.den / $1)};}
    fraction operator /(const fraction &rhs) const {return (*this) * rhs.reciprocal();}

    friend ostream &operator <<(ostream &os, const fraction &frac)
    {if (frac.den) os << frac.num << "/" << frac.den; else os << "NaN"; return os;}
};

namespace Geo
{
    using number = longs;

    const long double eps = fraction<longs>::$eps;
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
        auto length() const {return sqrt(dot(*this));}
        auto distance(const point &b) const {return (*this - b).length();}
        auto distance(const point &ls, const point &rs) const
        {return fabs((ls - *this).cross(rs - *this)) / ls.distance(rs);}
        point normal() const {return (x || y) ? *this / length() : point(0, 0);}
        auto angle() const {return atan2(y, x);}
        point rotate(number a) const
        {number c = cos(a), s = sin(a); return {c * x - s * y, s * x + c * y};}
        point perpendicular() const {return {-y, x};}
        point symmetry() const {return {-x, -y};}
        number square() const { return x * x + y * y; }
    };
}

template <class T> int sgn(T t) {return t ? (t < 0 ? -1 : 1) : t;}

using point = Geo::point;
using frac = fraction<longs>;

const int N = 2060;

point a[N];
vector<frac> li;

frac cosLemmaSquare(const point &p1, const point &p2)
{
    auto aa = p1.square(), bb = (p2 - p1).square(), cc = p2.square();
    longs x = bb + cc - aa, f = sgn(x);
    return {f * x * x, 4ll * bb * cc};
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    longs n, ans = 1;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i].x >> a[i].y;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++ j)
            if (a[i].cross(a[j]) > 0)
                li.push_back(cosLemmaSquare(a[i], a[j]));
        sort(li.begin(), li.end());
        longs len = li.size(), l = 0;
        while (l < len)
        {
            auto r = l;
            while (r < len && li[r] == li[l]) ++ r;
            ans = max(ans, r - l + 1);
            l = r;
        }
        li.clear();
    }
    cout << ans << endl;

    return 0;
}