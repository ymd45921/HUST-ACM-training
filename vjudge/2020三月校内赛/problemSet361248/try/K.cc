/**
 *
 * 计算几何题
 * 
 * 科普：
 * - 叉乘可以用来判断顺逆时针/凹凸多边形；这也可以使用Green公式
 * - 多边形相邻三个点叉乘：<0 顺时针，凸； >0 逆时针，凹
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
    longd operator *(const point& rhs) const;   // 点乘
    point operator *(longd rhs) const;          // 数乘
    point operator *(double rhs) const;
    point& operator +=(const point& rhs);
    point& operator -=(const point& rhs);
    point& operator *=(longd rhs);
    point& operator *=(double rhs);

    longd cross(const point& rhs) const;        // 叉乘模：平行四边形面积
    longd length() const;                       // 向量的模
    point normal() const;                       // 单位化向量
    longd distance(const point& b) const;       // 到某点的距离
    longd distance(const point& ls,const point& rs) const;  // 到直线ls-rs的距离
    void println();                             // 一行输出坐标
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
    longd angle = acos(a*b) / 2;    // 计算夹角的1/2
    point k = (a+b).normal();       // 角平分线的单位向量
    return k * (R / sin(angle));    // 返回满足垂直距离≥R的相对坐标
}

bool intersect(point& x,point& ls,point& rs)    // 相交（距离不足）返回false
{
    if ((ls-x)*(rs-ls) > 0) return x.distance(ls) >= r-eps; // x在ls的远端
    if ((rs-x)*(ls-rs) > 0) return x.distance(rs) >= r-eps;
    return x.distance(ls,rs) >= r-eps;          // x在直线ls-rs的正上方
}

bool test(point& x)     // 遍历检查点到所有边的距离
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
        if ((p[i]-p[i-1]).cross(p[i+1]-p[i]) > 0)   // 跳过多边形的凹角
            continue;
        auto tmp = p[i] + calculate(p[i-1]-p[i],p[i+1]-p[i]);   // 得到绝对位置
        if (test(tmp)) v.push_back(tmp);
    }

    bool found = false;
    for (auto& p1 : v) for (auto& p2 : v)
        if (p1.distance(p2) >= r2)          // 判断两个点之间的距离
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
point& point::operator +=(const point& rhs) {x += rhs.x; y += rhs.y; return THIS;}
point& point::operator -=(const point& rhs) {x -= rhs.x; y -= rhs.y; return THIS;}
point& point::operator *=(longd rhs) {x *= rhs; y *= rhs; return THIS;}
point& point::operator *=(double rhs) {x *= rhs; y *= rhs; return THIS;}

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