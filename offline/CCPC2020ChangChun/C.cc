/**
 *
 * 不得不说这个平面几何挺白给的，，竟然还没什么人做
 * 这不做出来不是血亏== 有板子复制粘贴完事（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#endif

template <class printable>
void trace(const char *name, printable &&value)
{cerr << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    cerr.write(names, separate - names) << " = " << value << ',';
    trace(separate + 1, list...);
}

template <class T>
void print(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
void print(char ch) {putchar(ch);}
template <class T, class ...Ts>
void print(T x, Ts ...xs) {print(x), print(xs...);}
void println() {puts("");}
template <class T>
void println(T x)
{print(x), putchar('\n');}

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

    static inline bool isBlank(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
    template <class T, class... Ts>
    void operator()(T &&x, Ts &&... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

namespace Geo
{
    using number = double;
    const number eps = 0;

    int _sgn(number x) {return x < -eps ? -1 : x > eps;}
    int compareTo(number a, number b) {return _sgn(a - b);}

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

        [[nodiscard]] int compareTo(const point &rhs) const {return _sgn(rhs.x * y - x * rhs.y);}
        [[nodiscard]] int equals(const point &rhs) const {return x == rhs.x && y == rhs.y;}
        bool operator <(const point &rhs) const {return rhs.x * y - x * rhs.y < 0;}
        bool operator <=(const point &rhs) const {return rhs.x * y - x * rhs.y <= 0;}
        bool operator >(const point &rhs) const {return rhs.x * y - x * rhs.y > 0;}
        bool operator >=(const point &rhs) const {return rhs.x * y - x * rhs.y >= 0;}

        [[nodiscard]] number dot(const point &rhs) const {return x * rhs.x + y * rhs.y;}
        [[nodiscard]] number cross(const point &rhs) const {return rhs.y * x - rhs.x * y;}
        [[nodiscard]] auto length() const {return sqrt(dot(*this));}
        [[nodiscard]] auto distance(const point &b) const {return (*this - b).length();}
        [[nodiscard]] auto distance(const point &ls, const point &rs) const
        {return fabs((ls - *this).cross(rs - *this)) / ls.distance(rs);}
        [[nodiscard]] point normal() const {return (x || y) ? *this / length() : point(0, 0);}
        [[nodiscard]] auto angle() const {return atan2(y, x);}
        [[nodiscard]] point rotate(number a) const
        {number c = cos(a), s = sin(a); return {c * x - s * y, s * x + c * y};}
        [[nodiscard]] point perpendicular() const {return {-y, x};}
        [[nodiscard]] point symmetry() const {return {-x, -y};}
        [[nodiscard]] number square() const { return x * x + y * y; }
    };

    struct line
    {
        point s, t;

        line() = default;
        line(number a, number b, number x, number y) : s(a, b), t(x, y) {}
        line(const point &s, const point &t) : s(s), t(t) {}
    };

    // 判断点和直线的位置关系： 左侧返回1； 共线返回0； 右侧返回-1；
    int onLeft(const point p, const line l)
    {
        number xx = (l.t - l.s).cross(p - l.s);
        return _sgn(xx);
    }

    // 判断两条线段是否存在交点的跨立实验
    bool straddleTest(const line a, const line b)
    {
        if (!(min(a.s.x, a.t.x) <= max(b.s.x, b.t.x) &&
              min(b.s.y, b.t.y) <= max(a.s.y, a.t.y) &&
              min(b.s.x, b.t.x) <= max(a.s.x, a.t.x) &&
              min(a.s.y, b.t.y) <= max(b.s.y, b.t.y)))
            return false;
        int asb = onLeft(a.s, b), atb = onLeft(a.t, b),
            bsa = onLeft(b.s, a), bta = onLeft(b.t, a);
        return asb && bsa && asb == -atb && bsa == -bta;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        L = scanner.nextInt(),
        q = scanner.nextInt();
    vector<Geo::point> list;
    for (int i = 0; i < n; ++ i)
    {
        int x = scanner.nextInt(),
            y = scanner.nextInt();
        list.emplace_back(x, y);
    }
    const auto S = Geo::point(0, 0);
    const auto T = Geo::point(L, 0);
    vector<Geo::number> far(n);
    using Geo::onLeft, Geo::straddleTest;
    for (int i = 0; i < n; ++ i)
    {
        const auto &ii = list[i];
        if (!sgn(ii.y)) continue;
        int saDir = sgn(ii.y) * -1,
            atDir = sgn(ii.y);
        auto tmp = ii.distance(T);
        auto SA = Geo::line(S, ii);
        auto AT = Geo::line(ii, T);
        for (const auto &jj : list)
        {
            if (onLeft(jj, SA) != saDir ||
                onLeft(jj, AT) != atDir)
                continue;
            auto upd = jj.distance(ii) + jj.distance(T);
            maximize(tmp, upd);
        }
        far[i] = tmp;
    }
    cout << fixed << setprecision(12);
    const auto st = Geo::line(S, T);
    while (q --)
    {
        int a = scanner.nextInt() - 1,
            b = scanner.nextInt() - 1;
        const auto &aa = list[a];
        const auto &bb = list[b];
        const auto ab = Geo::line(aa, bb);
        if (!Geo::straddleTest(st, ab))
            cout << (Geo::number)L << endl;
        else
        {
            const auto aDis = aa.distance(S),
                bDis = bb.distance(S),
                abDis = aa.distance(bb);
            auto ans = min(min(aDis + far[a], aDis + abDis + bb.distance(T)),
                           min(bDis + abDis + aa.distance(T), bDis + far[b]));
            cout << ans << endl;
        }
    }
    return 0;
}