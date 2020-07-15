/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>

namespace Geo
{
    using number = long double;
    const double eps = 1e-8;

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

        bool operator <(const point &rhs) const {return cross(rhs) < 0;}
    };
}

using namespace std;
using longs = long long;
using uint = unsigned;
using Geo::point;
using Geo::compareTo;

const int N = 2060;
point v[N];

inline int nextInt()
{
    int x = 0, f = 1, ch = getchar();
    while (!isdigit(ch)) if (ch == '-') f = -1, ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return x * f;
}

auto cosLemma(const point &a, const point &b)
{
    auto d = a - b;
    auto aa = a * a, bb = b * b, cc = d * d;
    return (aa + cc - bb) / (2 * a.length() * b.length());
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i)
        cin >> v[i].x >> v[i].y;
    if (n <= 2) return cout << n << endl, 0;
    sort(v, v + n);
    longs ans = 2;
    const int ii = n - 2, jj = n - 1;
    for (int i = 0; i < ii; ++ i)
        for (int j = i + 1; j < jj; ++ j)
        {
            const auto c = fabs(cosLemma(v[i], v[j]));
            if (!compareTo(c, 1)) continue;
            longs tmp = 2;
            for (int k = j + 1; k < n; ++ k)
            {
                const auto d = fabs(cosLemma(v[k], v[j]));
                if (!compareTo(c, d)) ++ tmp;
            }
            ans = max(ans, tmp);
        }
    cout << ans << endl;

    return 0;
}