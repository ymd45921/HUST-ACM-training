/**
 * 
 */
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
using longs = long long;
using longd = long double;
using ulongs = unsigned long long;

const int inf = 0x3f3f3f3f;
const longs INF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

namespace Geo
{
    using number = int;

    int compareTo(number x) { return x < -eps ? -1 : x > eps; }

    int compareTo(number a, number b) { return compareTo(a - b); }

    struct point
    {
        number x, y;

        point() = default;

        point(number x, number y) : x(x), y(y) {}

        point operator+(const point &rhs) const { return {x + rhs.x, y + rhs.y}; }

        point operator-(const point &rhs) const { return {x - rhs.x, y - rhs.y}; }

        number operator*(const point &rhs) const { return x * rhs.x + y * rhs.y; }

        point operator*(const number rhs) const { return {rhs * x, rhs * y}; }

        point operator/(const number rhs) const { return {x / rhs, y / rhs}; }

        point &operator+=(const point &rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        point &operator-=(const point &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        point &operator*=(const number rhs)
        {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        point &operator/=(const number rhs)
        {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        bool operator==(const point &rhs) const { return x == rhs.x && y == rhs.y; }

        bool operator!=(const point &rhs) const { return !(rhs == *this); }

        number dot(const point &rhs) const { return x * rhs.x + y * rhs.y; }

        number cross(const point &rhs) const { return rhs.y * x - rhs.x * y; }

        number length() const { return sqrt(dot(*this)); }

        number distance(const point &b) const { return (*this - b).length(); }

        number distance(const point &ls, const point &rs) const
        {
            return fabs((ls - *this).cross(rs - *this)) / ls.distance(rs);
        }

        point normal() const { return (x || y) ? *this / length() : point(0, 0); }

        number angle() const { return atan2(y, x); }

        point rotate(number a) const
        {
            number c = cos(a), s = sin(a);
            return {c * x - s * y, s * x + c * y};
        }

        point perpendicular() const { return {-y, x}; }

        point symmetry() const { return {-x, -y}; }

        bool operator<(const point &rhs) const
        {
            auto ll = 1ll * y * rhs.x;
            auto rr = 1ll * x * rhs.y;
            return ll < rr;
        }

        bool operator>(const point &rhs) const
        {
            auto ll = 1ll * y * rhs.x;
            auto rr = 1ll * x * rhs.y;
            return ll > rr;
        }
    };
}


const int N = 1e5 + 5;
int n, m, upto, dp[N];
Geo::point p[N], v[N];

int binary(const Geo::point &now)
{
    int ll = 1, rr = upto, res = 0;
    auto ii = Geo::point(m - now.x, -now.y);
    while (ll <= rr)
    {
        int mid = ll + rr >> 1;
        if (v[mid] < ii) res = mid, ll = mid + 1;
        else rr = mid - 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m)
    {
        auto pp = Geo::point(m, 0);
        for (int i = 1; i <= n; ++ i)
            cin >> p[i].x >> p[i].y;
        sort(p + 1, p + 1 + n, greater<Geo::point>());
        upto = 0;
        for (int i = 1; i <= n; ++ i)
        {
            dp[i] = binary(p[i]) + 1;
            v[dp[i]] = pp - p[i];
            upto = max(upto, dp[i]);
        }
        cout << upto << endl;
    }

    return 0;
}