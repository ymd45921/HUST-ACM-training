/**
 *
 * 首先，考虑到可以满足要求的两个新位置
 * 其到源点的斜率一定相等
 *
 * 而一个点可以对应两种操作，即两个不同的斜率
 * 所以，我们可以将两个斜率之间连边
 * 那么问题转化为以斜率为节点的图，寻找边的匹配
 * 匹配的两条边需要至少共享一个节点端点
 * 这可以 DFS 完成维护：
 * - 对于斜率 u，有边 u->v；如果 v 的 DFS 树中有多余的未匹配边
 *   那么显然可以和边 u->v 匹配，因为它们共享了端点 v
 * - 否则，继续寻找 u 的下一条可用出边 u->w，如果 w 也无法接续
 *   那么显然可以和之前剩下的 u->v 匹配，因为它们共享了端点 u
 * - 首先，如果 DFS 图中只有树边，那很显然这么做是正确的
 * - 现在，我们考虑在图中加入部分非后向边：
 *   因为匹配到前向边/交叉边的时候，端点的子树一定已经完全匹配了
 *   （就本题代码来看，这些点已经被标记为 2 退出了）
 *   所以它的位置一定不存在残留，残留的边都聚集在根节点周围
 *   那些已经匹配的边可以不用考虑了，匹配也仅限于残留和其他前向边
 * - 综上所述，这样的匹配是合理的
 * 虽然但是，除了基本的思维就是考察 DFS 相关的知识了（
 */
#include <bits/stdc++.h>

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
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
        sprintf(buffer, "%.10lf", x), write(io, buffer);
    }

    static void write(FILE *io, const long double x) {
        sprintf(buffer, "%.10Lf", x), write(io, buffer);
    }

    static void write(FILE *io, const float x) {
        sprintf(buffer, "%f", x), write(io, buffer);
    }

    static void write(FILE *io, const char *const x) { fputs(x, io); }

    static void write(FILE *io, char *const x) { fputs(x, io); }

    static void write(FILE *io, const std::string &x) { write(io, x.c_str()); }

    static void write(FILE *io, const char x) { fputc(x, io); }

    static void write(FILE *io, const bool x) { fputs(x ? "true" : "false", io); }

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

    bool tryNext() {
        int ch = ::getchar();
        if (ch == -1) return false;
        ch = ungetc(ch, stdin);
        return this, ch != EOF;
    }

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

    cquery &nextLine(char *str) {
        int ch = ::getchar();
        while (is<_blank>(ch)) ch = ::getchar();
        str[0] = (char) ch;
        scanf("%[^\n]", str + 1);
        return ::getchar(), *this;
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

namespace Frac {
    using decimal = long long;
    using number = double;
    using bigInt = __int128;

    const number eps = 1e-8;

    int _sgn(number x) { return x < -eps ? -1 : x > eps; }

    int compareTo(number a, number b) { return _sgn(a - b); }

    class frac {
        decimal num, den;

        [[nodiscard]] auto cmp(const frac &rhs) const { return (bigInt) num * rhs.den - (bigInt) den * rhs.num; }

    public:

        frac() = default;

        frac(decimal u, decimal v) : num(u), den(v) { if (!v) num = 0; else if (v < 0) num = -u, den = -v; }

        explicit frac(decimal x) : num(x), den(1) {}

        frac &reduce() {
            auto x = gcd(num, den);
            num /= x, den /= x;
            return *this;
        }

        [[nodiscard]] auto atan2() const { return std::atan2(den, num); }

        [[nodiscard]] auto numerator() const { return num; }

        [[nodiscard]] auto denominator() const { return den; }

        void numerator(decimal x) { num = x; }

        void denominator(decimal x) { den = x; }

        frac &normal() {
            reduce();
            if (den < 0) den = -den, num = -num;
            return *this;
        }

        [[nodiscard]] bool nan() const { return den == 0; }

        [[nodiscard]] number toNumber() const { return (number) num / den; }

        [[nodiscard]] int compareTo(const frac &rhs) const { return Frac::compareTo(toNumber(), rhs.toNumber()); }

        [[nodiscard]] bool equals(const frac &rhs) const {
            return nan() || rhs.nan() ? !(nan() ^ rhs.nan()) : !compareTo(rhs);
        }

        bool operator==(const frac &rhs) const { return nan() || rhs.nan() ? nan() == rhs.nan() : !cmp(rhs); }

        bool operator<(const frac &rhs) const { return cmp(rhs) < 0; }

        bool operator>(const frac &rhs) const { return cmp(rhs) > 0; }

        bool operator!=(const frac &rhs) const { return !(*this == rhs); }

        frac operator-() const { return frac(-num, den); }

        frac operator~() const { return frac(den, num); }

        frac operator+(const frac &rhs) const {
            auto x = gcd(den, rhs.den);
            return frac(rhs.den / x * num + den / x * rhs.num, den / x * rhs.den);
        }

        frac operator-(const frac &rhs) const { return (*this) + -rhs; }

        frac operator*(const frac &rhs) const {
            auto _1 = gcd(abs(num), rhs.den), _2 = gcd(abs(rhs.num), den);
            return frac(num / _1 * (rhs.num / _2), den / _2 * (rhs.den / _1));
        }

        frac operator/(const frac &rhs) const { return (*this) * ~rhs; }

        frac &operator+=(const frac &rhs) { return *this = *this + rhs; }

        frac &operator-=(const frac &rhs) { return *this = *this - rhs; }

        frac &operator*=(const frac &rhs) { return *this = *this * rhs; }

        frac &operator/=(const frac &rhs) { return *this = *this / rhs; }

        bool operator<=(const frac &rhs) const { return !(*this > rhs); }

        bool operator>=(const frac &rhs) const { return !(*this < rhs); }
    };
}

const int N = 2e5 + 5;
using Frac::frac;
pair<frac, frac> p[N];
array<int, N> vis;
vector<vector<pair<int, int>>> g;
vector<pair<int, int>> ans;

int dfs(int u) {
    vis[u] = 1;
    int cur = -1;
    for (auto [v, ii] : g[u]) {
        if (vis[v] == 1) continue;
        int now = ii;
        if (!vis[v]) {
            int tmp = dfs(v);
            if (tmp != -1) {
                ans.emplace_back(now, tmp);
                now = -1;
            }
        }
        if (now != -1)
            if (cur != -1) {
                ans.emplace_back(cur, now);
                cur = -1;
            } else cur = now;
        else;
    }
    return vis[u] = 2, cur;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int n = $.nextInt(), a, b, c, d;
    g.resize(2 * n + 1);
    map<frac, int> id;
    int tot = 0;
    const auto one = frac(1);
    for (int i = 1; i <= n; ++ i) {
        $(a, b, c, d);
        auto x = frac(a, b), y = frac(c, d);
        p[i] = pair(x.reduce(), y.reduce());
        auto k1 = (y + one) / x, k2 = y / (x + one);
        k1.normal(), k2.normal();
        if (!id[k1]) id[k1] = ++ tot;
        if (!id[k2]) id[k2] = ++ tot;
        g[id[k1]].emplace_back(id[k2], i);
        g[id[k2]].emplace_back(id[k1], i);
    }
    for (int i = 1; i <= tot; ++ i)
        if (!vis[i]) dfs(i);
    $.put(ans.size());
    for (auto [a, b] : ans) $.put(a, b);

    return 0;
}