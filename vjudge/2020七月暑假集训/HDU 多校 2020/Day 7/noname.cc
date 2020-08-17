/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <bitset>

#define number double
#define nextDouble() static_cast<number>(nextInt())
#define check(T, L) (T[L.first] = T[L.second] = true)
#define linked(L) (last[L.first] || last[L.second])

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace Geo
{
    constexpr number eps = 0;
    int sgn(number x) {return x < -eps ? -1 : x > eps;}
    int compareTo(number a, number b) {return sgn(a - b);}

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

using Geo::point;
using Geo::compareTo;

constexpr int N = 2060;
point v[N];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt();
        for (int i = 1; i <= n; ++ i)
            v[i] = {nextDouble(), nextDouble()};
        priority_queue<pair<number, pair<int, int>>> list;
        for (int i = 1; i <= n; ++ i)
            for (int j = i + 1; j <= n; ++ j)
                list.push({v[i].distance(v[j]), {i, j}});
        bool status = true;
        bitset<N> last, now;
        last = ~last;
        while (!list.empty())
        {
            while (!list.empty() &&
                !linked(list.top().second))
                list.pop();
            if (list.empty()) break;
            auto xx = list.top().first;
            while (!list.empty() &&
                !compareTo(list.top().first, xx))
                check(now, list.top().second), list.pop();
            if (now[1]) break;
            last = now, now.reset();
            status = !status;
        }
        if (status) puts("YES"); else puts("NO");
    }

    return 0;
}