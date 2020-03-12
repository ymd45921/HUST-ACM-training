/**
 *
 * 计算几何题
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

#define THIS (*this)

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

class point
{
public:
    longd x, y;

    point operator +(const point& rhs) const;
    point operator -(const point& rhs) const;
    longd operator *(const point& rhs) const;
    point operator *(longd rhs) const;
    point operator /(longd rhs) const;
    point operator *(double rhs) const;
    point& operator +=(const point& rhs);
    point& operator -=(const point& rhs);
    point& operator *=(longd rhs);
    point& operator *=(double rhs);
    point& operator /=(longd rhs);
    longd cross(const point& rhs) const;
    longd length() const;
    point normal() const;
    longd distance(const point& b) const;
    longd distance(const point& ls,const point& rs) const;
    void println();
};

const int R = 4000;
const double r = 4000;
const double eps = 1e-3;
const double r2 = 2*r - eps;
const int N = 2060;
int n;
point p[N];
vector<point> v;

point calculate(point a,point b)
{
    a = a.normal();
    b = b.normal();
    longd angle = acos(a*b) / 2;
    point k = (a+b).normal();
    return k * (R / sin(angle));
}

bool intersect(point& x,point& ls,point& rs)   // 相交返回false
{
    if ((ls-x)*(rs-ls) > 0) return x.distance(ls) >= r-eps;
    if ((rs-x)*(ls-rs) > 0) return x.distance(rs) >= r-eps;
    return x.distance(ls,rs) >= r-eps;
}

bool test(point& x)
{
    for (int i = 1; i <= n; ++ i)
        if (!intersect(x,p[i-1],p[i])) return false;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for (int i = 1; i <= n; ++ i)
        cin >> p[i].x >> p[i].y;
    p[0] = p[n]; p[n+1] = p[1];

    for (int i = 1; i <= n; ++ i)
    {
        if ((p[i]-p[i-1]).cross(p[i+1]-p[i]) > 0)
            continue;
        auto tmp = p[i] + calculate(p[i-1]-p[i],p[i+1]-p[i]);
        if (test(tmp)) v.push_back(tmp);
    }

    bool found = false;
    for (auto& p1 : v) for (auto& p2 : v)
        if (p1.distance(p2) >= r2)
        {
            cout<<fixed<<setprecision(10);
            p1.println();
            p2.println();
            found = true; goto END;
        }

    END:
    if(!found) cout<<"impossible"<<endl;
    return 0;
}

point point::operator +(const point& rhs) const {return (point){x + rhs.x, y + rhs.y};}
point point::operator -(const point& rhs) const {return (point){x - rhs.x, y - rhs.y};}
longd point::operator *(const point& rhs) const {return x * rhs.x + y * rhs.y;}
point point::operator *(const longd rhs) const {return (point){rhs * x, rhs * y};}
point point::operator *(const double rhs) const {return (point){rhs * x, rhs * y};}
point point::operator /(longd rhs) const {return (point){x / rhs, y / rhs};}
point& point::operator +=(const point& rhs) {x += rhs.x; y += rhs.y; return THIS;}
point& point::operator -=(const point& rhs) {x -= rhs.x; y -= rhs.y; return THIS;}
point& point::operator *=(longd rhs) {x *= rhs; y *= rhs; return THIS;}
point& point::operator *=(double rhs) {x *= rhs; y *= rhs; return THIS;}
point& point::operator /=(longd rhs) {x /= rhs; y /= rhs; return THIS;}

longd point::cross(const point& rhs) const {return rhs.y * x - rhs.x * y;}

longd point::length() const {return sqrtl(THIS*THIS);}

point point::normal() const
{
    longd l = this->length();
    return (point){x/l,y/l};
}

longd point::distance(const point& b) const {return (THIS-b).length();}

longd point::distance(const point& ls,const point& rs) const
{
    return fabsl((ls-THIS).cross(rs-THIS))/ls.distance(rs);
}

void point::println() {cout << x << ' ' << y << endl;}