/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>

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

namespace Geo
{
    using number = long double;
    const number eps = 1e-8;

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

    struct line
    {
        point s, t;

        line() = default;
        line(number a, number b, number x, number y) : s(a, b), t(x, y) {}
        line(const point &s, const point &t) : s(s), t(t) {}
    };

    // 判断点和直线的位置关系： 左侧返回1； 共线返回0； 右侧返回-1；
    int onLeft(point p, line l)
    {
        number xx = (l.t - l.s).cross(p - l.s);
        return compareTo(xx);
    }
}

using point = Geo::point;
using number = Geo::number;
using Geo::compareTo;

point p[25];
number d[25];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    cin >> t;
    while (t --)
    {
        for (int i = 0; i < 20; ++ i)
            cin >> p[i].x >> p[i].y;
        d[0] = p[0].distance(p[19]);
        for (int i = 1; i < 20; ++ i)
            d[i] = p[i].distance(p[i - 1]);
        int xp = 0; number xx = 0;
        for (int i = 0; i < 20; ++ i)
            if (compareTo(d[i], xx) > 0) xx = d[i], xp = i;
        auto hand = Geo::line(p[xp], p[(xp + 19) % 20]);
        auto &ff = p[(xp + 18) % 20], &bb = p[(xp + 1) % 20];
        if (Geo::onLeft(ff, hand) > 0)  // counterclockwise
            if (compareTo(d[(xp + 1) % 20], d[(xp + 19) % 20]) > 0)
                cout << "left" << endl;
            else cout << "right" << endl;
        else                            // clockwise
            if (compareTo(d[(xp + 1) % 20], d[(xp + 19) % 20]) > 0)
                cout << "right" << endl;
            else cout << "left" << endl;
    }

    return 0;
}