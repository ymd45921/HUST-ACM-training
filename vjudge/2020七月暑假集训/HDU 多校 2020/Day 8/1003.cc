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
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

namespace Geo
{
    using number = double;
    const number eps = 0;

    int compareTo(number x) {return x < -eps ? -1 : x > eps;}
    int compareTo(number a, number b) {return compareTo(a-b);}

    struct point
    {
        number x, y;

        point() = default;
        point(number x, number y) : x(x), y(y) {}
        double angle() const {return atan2(y, x);}
    };
}

Geo::point p[3];
int seq[3];
double ang[3];

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        for (auto & i : p)
            i.x = nextInt(), i.y = nextInt();
        seq[0] = 1, seq[1] = 2, seq[2] = 3;
        for (int i = 0; i < 3; ++ i)
            ang[i] = p[i].angle();
        double minn = ang[0];
        int ind = 0;
        if (ang[1] < minn && ang[1] < ang[2]) minn = ang[1], ind = 1;
        else if (ang[2] < minn && ang[2] < ang[1]) minn = ang[2], ind = 2;
        bool dir = ang[(ind + 1) % 3] > ang[(ind + 2) % 3];
        dir ? puts("Clockwise") : puts("Counterclockwise");
    }

    return 0;
}