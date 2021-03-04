/**
 *
 * 好家伙，几脚排序，这不是经典做法🐎
 * 好家伙，n²log n 能过，好家伙
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x 
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

template <class T>
void println(const T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}

static class Scanner 
{
    template<class T>
    inline T read()
    {
        T x = 0; int f = 0, ch = getchar();
        while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
        return f ? -x : x;
    }

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}    
} scanner;

using number = longs;
const number eps = 0;

int sgn(number x) {return x < -eps ? -1 : x > eps;}
int compareTo(number a, number b) {return sgn(a-b);}

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
    int compareTo(const point &rhs) const {return sgn(rhs.x * y - x * rhs.y);}
};

const int N = 4080;

struct monument
{longs x, y, g;}
a[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        scanner(a[i].x, a[i].y, a[i].g);
        
    

    return 0;
}

