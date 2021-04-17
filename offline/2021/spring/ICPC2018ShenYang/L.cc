#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define $$(...) $.trace(#__VA_ARGS__, __VA_ARGS__)

static class cquery {

    static constexpr char _blank[] = " \n";
    static constexpr char _break[] = "\n";
    static constexpr size_t buffer_size = 100;
    static char buffer[buffer_size];

    template<class T>
    inline T read() {
        T ret = 0;
        int f = 0, ch = ::getchar();
        for (; !isdigit(ch); ch = ::getchar())
            if (ch == '-') f = !f;
        for (; isdigit(ch); ch = ::getchar())
            ret = ret * 10 + ch - 48;
        return f ? -ret : ret;
    }

    template<class T>
    static void write(FILE *io, T x) {
        if (x < 0) {
            fputc('-', io);
            x = -x;
        }
        static char *str = buffer;
        int cnt = 0;
        while (x > 9) {
            str[cnt++] = (x % 10) + 48;
            x /= 10;
        }
        str[cnt++] = x + 48;
        while (cnt--) fputc(str[cnt], io);
    }

    static void write(FILE *io, const double x) {
        sprintf(buffer, "%lf", x), write(io, buffer);
    }

    static void write(FILE *io, const long double x) {
        sprintf(buffer, "%Lf", x), write(io, buffer);
    }

    static void write(FILE *io, const float x) {
        sprintf(buffer, "%f", x), write(io, buffer);
    }

    static void write(FILE *io, const char *const x) { fputs(x, io); }

    static void write(FILE *io, char *const x) { fputs(x, io); }

    static void write(FILE *io, const std::string &x) { write(io, x.c_str()); }

    static void write(FILE *io, const char x) { fputc(x, io); }

    template<const char *charset>
    static inline bool is(int x) {
        if (x <= 0) return true;
        const char *syb = charset;
        for (; *syb; ++syb) if (*syb == x) return true;
        return false;
    }

    template<class T, class ...Ts>
    void write(FILE *io, const T &x, Ts ...xs) {
        write(io, x), write(io, xs...);
    }

    template<class T, class ...Ts>
    void write(FILE *io, const T &&x, Ts ...xs) {
        write(io, x), write(io, xs...);
    }

    static char *readToken() {
        char *cur = buffer;
        int ch = ::getchar();
        while (is<_blank>(ch)) ch = ::getchar();
        for (; !is<_blank>(ch); ch = ::getchar())
            *cur++ = (char) ch;
        return *cur = '\0', cur;
    }

    static void flush(FILE *stream) { fflush(stream); }

    static int eof(FILE *stream) { return feof(stream); }

public:

    template<class T>
    cquery &operator()(T &x) {
        x = read<T>();
        return *this;
    }

    template<class T, class... Ts>
    cquery &operator()(T &x, Ts &... y) {
        return (*this)(x), (*this)(y...);
    }

    template<class... Ts>
    cquery &operator()(char *x, Ts &... y) {
        return (*this)(x), (*this)(y...);
    }

    cquery &operator()(char *x) {
        scanf("%s", x);
        return *this;
    }

    cquery &operator()(double &x) {
        auto end = readToken();
        x = strtod(buffer, &end);
        return *this;
    }

    cquery &operator()(long double &x) {
        auto end = readToken();
        x = strtold(buffer, &end);
        return *this;
    }

    cquery &operator()(float &x) {
        auto end = readToken();
        x = strtof(buffer, &end);
        return *this;
    }

    template<class T1, class T2>
    cquery &operator()(std::pair<T1, T2> &x) {
        return (*this)(x.first, x.second);
    }

    cquery &operator()(char &x) {
        do x = (char) ::getchar(); while (is<_blank>(x));
        return *this;
    }

private:

    template<class T>
    T next() {
        T ret;
        (*this)(ret);
        return ret;
    }

public:

    int nextInt() { return read<int>(); }

    auto nextLong() { return read<long long>(); }

    auto next128() { return read<__int128>(); }

    char getchar() { return next<char>(); }

    double nextDouble() { return next<double>(); }

    auto nextFloat() { return next<float>(); }

    cquery &flush() { return flush(stdout), *this; }

    bool hasNext() { return this, !eof(stdin); }

    template<class T>
    cquery &print(const T &x) { return write(stdout, x), *this; }

    template<class T>
    cquery &print(const T &&x) { return write(stdout, x), *this; }

    template<class T, class ...Ts>
    cquery &print(T &x, Ts ...xs) {
        return write(stdout, x, xs...), *this;
    }

    template<class T, class ...Ts>
    cquery &print(T &&x, Ts ...xs) {
        return write(stdout, x, xs...), *this;
    }

    template<class T>
    cquery &println(const T &x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T>
    cquery &println(const T &&x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &println(const T &x, Ts ...xs) {
        return write(stdout, x, xs..., '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &println(const T &&x, Ts ...xs) {
        return write(stdout, x, xs..., '\n'), *this;
    }

    template<class T>
    cquery &put(const T &x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T>
    cquery &put(const T &&x) {
        return write(stdout, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &put(const T &x, Ts ...xs) {
        write(stdout, x, ' '), put(xs...);
        return *this;
    }

    template<class T, class ...Ts>
    cquery &put(const T &&x, Ts ...xs) {
        write(stdout, x, ' '), put(xs...);
        return *this;
    }

    template<class T>
    cquery &nextArray(T first, T last) {
        while (first != last)
            (*this)(*first), ++first;
        return *this;
    }

    template<class T, class Fun = void (*)(T, cquery &)>
    cquery &nextArray(T first, T last, Fun lambda) {
        while (first != last)
            lambda(first, *this), ++first;
        return *this;
    }

    template<class T>
    cquery &putArray(T first, T last, char split = ' ') {
        while (first != last) {
            write(stdout, *first), ++first;
            if (first != last) write(stdout, split);
            else write(stdout, '\n');
        }
        return *this;
    }

    template<class T>
    cquery &putArray(T first, T last, char *split) {
        while (first != last) {
            write(stdout, *first), ++first;
            if (first != last) write(stdout, split);
            else write(stdout, '\n');
        }
        return *this;
    }

    template<class T, class Fun = void (*)(T, cquery &), class comma = char>
    cquery &putArray(T first, T last, Fun fmt, comma split = ' ') {
        while (first != last) {
            fmt(first, *this), ++first;
            if (first != last) write(stdout, split);
            else write(stdout, '\n');
        }
        return *this;
    }

    template<class T>
    cquery &log(const T &x) {
        return write(stderr, x, '\n'), *this;
    }

    template<class T>
    cquery &log(const T &&x) {
        return write(stderr, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &log(const T &x, Ts ...xs) {
        write(stderr, x, ' '), log(xs...);
        return *this;
    }

    template<class T, class ...Ts>
    cquery &log(const T &&x, Ts ...xs) {
        write(stderr, x, ' '), log(xs...);
        return *this;
    }

    template<class T>
    cquery &logArray(T first, T last, char split = ' ') {
        while (first != last) {
            write(stderr, *first), ++first;
            if (first != last) write(stderr, split);
            else write(stderr, '\n');
        }
        return *this;
    }

    template<class T>
    cquery &logArray(T first, T last, char *split) {
        while (first != last) {
            write(stderr, *first), ++first;
            if (first != last) write(stderr, split);
            else write(stderr, '\n');
        }
        return *this;
    }

    template<class T, class Fun = void (*)(T, cquery &), class comma = char>
    cquery &logArray(T first, T last, Fun fmt, comma split = ' ') {
        while (first != last) {
            fmt(first, *this), ++first;
            if (first != last) write(stderr, split);
            else write(stderr, '\n');
        }
        return *this;
    }

    cquery &newLine() { return write(stdout, '\n'), *this; }

    [[deprecated]] cquery &println() { return newLine(); }

    [[deprecated]] cquery &put() { return newLine(); }

    template<class T>
    void trace(const char *name, T &&value) { write(stderr, name, " = ", value, '\n'); }

    template<class T, class ...Ts>
    void trace(const char *names, T &&value, Ts &&...list) {
        const char *separate = strchr(names + 1, ',');
        while (names != separate) fputc(*names++, stderr);
        write(stderr, " = ", value), fputc(',', stderr);
        trace(separate + 1, list...);
    }
} $;

char cquery::buffer[cquery::buffer_size];

struct {
    template<class token>
    auto &operator,(token &x) { return $(x), *this; }

    auto &operator,(char *x) { return $(x), *this; }
} input;

struct {
    using linebreak = std::ostream &(*)(std::ostream &);

    auto &operator,(linebreak x) { return $.newLine().flush(), *this; }

    template<class token>
    auto &operator,(token &x) { return $.print(x), *this; }

    template<class token>
    auto &operator,(token &&x) { return $.print(x), *this; }
} output;

using namespace std;

using longs = long long;
using uint = unsigned;
using lll = __int128;

const auto null = nullptr;

#include <cmath>

namespace Geo {
    using number = double;
    const number eps = 1e-8;

    using polar = pair<number, number>;

#ifndef sgn

    int sgn(number x) { return x < -eps ? -1 : x > eps; }

    template<class T>
    int sgn(T x) { return x < 0 ? -1 : x > 0; }

#endif

    int compareTo(number a, number b) { return sgn(a - b); }

    struct point {
        number x, y;

        point() = default;

        point(number x, number y) : x(x), y(y) {}

        static point polar(number r, number theta) { return point(r * cos(theta), r * sin(theta)); }

        point operator+(const point &rhs) const { return {x + rhs.x, y + rhs.y}; }

        point operator-(const point &rhs) const { return {x - rhs.x, y - rhs.y}; }

        number operator*(const point &rhs) const { return x * rhs.x + y * rhs.y; }

        point operator*(const number rhs) const { return {rhs * x, rhs * y}; }

        point operator/(const number rhs) const { return {x / rhs, y / rhs}; }

        point &operator+=(const point &rhs) {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        point &operator-=(const point &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        point &operator*=(const number rhs) {
            x *= rhs;
            y *= rhs;
            return *this;
        }

        point &operator/=(const number rhs) {
            x /= rhs;
            y /= rhs;
            return *this;
        }

        bool operator==(const point &rhs) const { return x == rhs.x && y == rhs.y; }

        bool operator!=(const point &rhs) const { return !(rhs == *this); }

#ifdef CXX_2A
        int operator <=>(const point &rhs) const {return sgn(rhs.x * y - x * rhs.y);}
#else

        int compareTo(const point &rhs) const { return sgn(rhs.x * y - x * rhs.y); }

        int equals(const point &rhs) const { return x == rhs.x && y == rhs.y; }

        bool operator<(const point &rhs) const { return rhs.x * y - x * rhs.y < 0; }

        bool operator<=(const point &rhs) const { return rhs.x * y - x * rhs.y <= 0; }

        bool operator>(const point &rhs) const { return rhs.x * y - x * rhs.y > 0; }

        bool operator>=(const point &rhs) const { return rhs.x * y - x * rhs.y >= 0; }

#endif

        number dot(const point &rhs) const { return x * rhs.x + y * rhs.y; }

        number cross(const point &rhs) const { return rhs.y * x - rhs.x * y; }

        auto length() const { return sqrt(dot(*this)); }

        auto distance(const point &b) const { return (*this - b).length(); }

        auto distance(const point &ls, const point &rs) const {
            return fabs((ls - *this).cross(rs - *this)) / ls.distance(rs);
        }

        point normal() const { return (x || y) ? *this / length() : point(0, 0); }

        auto angle() const { return atan2(y, x); }

        point rotate(number a) const {
            number c = cos(a), s = sin(a);
            return {c * x - s * y, s * x + c * y};
        }

        point perpendicular() const { return {-y, x}; }

        point symmetry() const { return {-x, -y}; }

        number square() const { return x * x + y * y; }

        Geo::polar polar() { return make_pair(length(), angle()); }
    };

    struct circle {
        point o;
        number r;

        circle() = default;

        explicit circle(number r, point c = {0, 0}) : r(r), o(c) {}

        circle(number r, number x, number y) : r(r), o(x, y) {}

        bool operator==(const circle &rhs) const { return (o == rhs.o) && (r == rhs.r); }

        bool operator!=(const circle &rhs) const { return (o != rhs.o) || (r != rhs.r); }

        pair<point, point> cross(const circle &rhs) const {
            if (*this == rhs) return {};
            const auto o2o = (rhs.o - o); // 必须用 rhs - lhs !!
            number dis = o2o.length();
            number a = acos((r * r + dis * dis - rhs.r * rhs.r) / (2 * r * dis));
            auto base = o2o.angle();
            return make_pair
                    (o + point::polar(r, base + a),
                     o + point::polar(r, base - a));
        }

        // 0 圆上，-1 圆外，1 圆内
        int relation(const point &p) const {
            auto dis = (p - o).length();
            return sgn(r - dis);
        }

        number diameter() { return r * 2; }
    };
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int T = $.nextInt(), n, r, x, y;
    vector<Geo::circle> del;
    vector<Geo::point> inter;
    const auto isAlive = [&](const Geo::point &p) -> bool {
        return all_of(del.begin(), del.end(), [&p](const Geo::circle &c) -> bool {
            return c.relation(p) < 0;
        });
    };
    for (int tCase = 1; tCase <= T; ++tCase) {
        input, n, r;
        Geo::circle O(r);
        del.clear(), inter.clear();
        while (n--) {
            input, x, y, r;
            del.emplace_back(r, x, y);
            auto[a, b] = O.cross(del.back());
            inter.push_back(a), inter.push_back(b);
        }
        bool isR = false;
        for (auto p : inter) {
            if (isAlive(p.symmetry())) {
                isR = true;
                break;
            }
        }
        $.print("Case #", tCase, ": ");
        if (isR) {
            $.put(O.diameter());
        } else {
            Geo::number ans = 0;
            for (auto i : inter)
                for (auto j : inter)
                    maximize(ans, (i - j).length());
            minimize(ans, O.diameter());
            printf("%.10f\n", ans);
        }
    }

    return 0;
}