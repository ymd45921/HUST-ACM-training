/**
 *
 * 原来是调用逻辑写错了啊，那没事了（
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

template <class T>
class seg_tree_lazy
{
    int siz;
    vector<T> maxima, lazy, sum;
    T init;
    static constexpr T zero = 0; // 零元
    T merge(T x, T y) { return max(x, y); }
    T combine(T x, T y) { return x + y; }

    void fix(int id)
    {
        maxima[id] = merge(maxima[id * 2 + 1], maxima[id * 2 + 2]);
        sum[id] = combine(sum[id * 2 + 1], sum[id * 2 + 2]);
    }

    void build(int id, int l, int r)
    {
        if (l + 1 == r)
        {
            maxima[id] = init;
            sum[id] = init;
            lazy[id] = 0;
            return;
        }
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m);
        build(id * 2 + 2, m, r);
        fix(id);
    }

    void update(int id, int l, int r, int pos, T val)
    {
        if (l + 1 == r) { maxima[id] = val; return;}
        int m = (l + r) / 2;
        push_down(id, l, r, m);
        if (pos < m) update(id * 2 + 1, l, m, pos, val);
        else update(id * 2 + 2, m, r, pos, val);
        fix(id);
    }

    T query(int id, int l, int r, int ll, int rr)
    {
        if (ll >= rr) return init;
        else if (ll == l && rr == r) return maxima[id];
        int m = (l + r) / 2;
        push_down(id, l, r, m);
        auto lv = query(id * 2 + 1, l, m, ll, min(rr, m));
        auto rv = query(id * 2 + 2, m, r, max(m, ll), rr);
        return merge(lv, rv);
    }

    T summation(int id, int l, int r, int ll, int rr)
    {
        if (ll >= rr) return zero;
        else if (ll == l && rr == r) return sum[id];
        int m = (l + r) / 2;
        push_down(id, l, r, m);
        auto lv = summation(id * 2 + 1, l, m, ll, min(rr, m));
        auto rv = summation(id * 2 + 2, m, r, max(m, ll), rr);
        return combine(lv, rv);
    }

    void tag_lazy(int id, int l, int r, T value)
    {
        lazy[id] = combine(lazy[id], value);
        const auto length = r - l;
        sum[id] = combine(sum[id], length * value);
        maxima[id] = combine(maxima[id], value);
    }

    void push_down(int id, int l, int r, int m)
    {
        if (lazy[id] == zero) return;
        tag_lazy(id * 2 + 1, l, m, lazy[id]);
        tag_lazy(id * 2 + 2, m, r, lazy[id]);
        lazy[id] = zero;
    }

    void add(int id, int l, int r, int ll, int rr, T value)
    {
        if (ll >= rr) return;
        if (l == ll && r == rr) return tag_lazy(id, l, r, value);
        int m = (l + r) / 2;
        push_down(id, l, r, m);
        if (ll < m) add(id * 2 + 1, l, m, ll, min(rr, m), value);
        if (rr > m) add(id * 2 + 2, m, r, max(m, ll), rr, value);
        fix(id);
    }

public:
    explicit seg_tree_lazy(int n = 0, T default_v = 0)
            : siz(n), init(default_v)
            {
        maxima.resize(4 * n);
        lazy.resize(4 * n);
        sum.resize(4 * n);
            }

    void resize(int n) {siz = n; maxima.resize(4 * n);}

    void build() {return build(0, 0, siz + 1);}

    void update(int pos, T val) {update(0, 0, siz + 1, pos, val);}

    void add(int ll, int rr, T val) {add(0, 0, siz + 1, ll, rr, val);}

    T query(int ll, int rr) {return query(0, 0, siz + 1, ll, rr);}

    T summation(int ll, int rr) {return summation(0, 0, siz + 1, ll, rr);}
};

char s[100];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

//    seg_tree_lazy<int> tree(11);
//    tree.build();
//    int ma[12], su[12];
//    for (int i = 1; i < 12; ++ i) {
//        ma[i] = tree.query(i, i + 1);
//        su[i] = tree.summation(i, i + 1);
//    }
//    $.logArray(ma + 1, ma + 12).logArray(su + 1, su + 12);
//    int op, l, r, x;
//    while (true) {
//        $(op, l, r);
//        if (op == 1) {
//            x = $.nextInt();
//            tree.add(l, r + 1, x);
//        } else $.put(tree.query(l, r + 1), tree.summation(l, r + 1));
//        for (int i = 1; i < 12; ++ i) {
//            ma[i] = tree.query(i, i + 1);
//            su[i] = tree.summation(i, i + 1);
//        }
//        $.logArray(ma + 1, ma + 12).logArray(su + 1, su + 12);
//    }

    int n, m, l, r;
    $(n, m);
    seg_tree_lazy<int> two(n + 1), three(n + 1),
            five(n + 1), seven(n + 1);
    two.build(), three.build(), five.build(), seven.build();
    while (m--) {
        $(s, l, r);
        if (s[1] == 'A') {
            $.put("ANSWER", max({
                two.query(l, r + 1),
                three.query(l, r + 1),
                five.query(l, r + 1),
                seven.query(l, r + 1)
            }));
        } else switch ($.nextInt()) {
            case 2:
                two.add(l, r + 1, 1);
                break;
            case 3:
                three.add(l, r + 1, 1);
                break;
            case 4:
                two.add(l, r + 1, 2);
                break;
            case 5:
                five.add(l, r + 1, 1);
                break;
            case 6:
                two.add(l, r + 1, 1);
                three.add(l, r + 1, 1);
                break;
            case 7:
                seven.add(l, r + 1, 1);
                break;
            case 8:
                two.add(l, r + 1, 3);
                break;
            case 9:
                three.add(l, r + 1, 2);
                break;
            case 10:
                two.add(l, r + 1, 1);
                five.add(l, r + 1, 1);
                break;
            default: break;
        }
    }

    return 0;
}