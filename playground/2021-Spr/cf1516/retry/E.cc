/**
 * 
 * 首先，我们考虑一种贪心的复原排列的方法：
 * - 从前往后，如果当前位置满足 p[i] = i，则跳过
 * - 否则，进行一次交换是的 p[i] = i 复位
 * 可以证明，如果有 n 个位置错位了，最多进行 n - 1 次交换
 * 
 * 基于这种方法，我们可以构造出 j 次交换可以复位的长度 n 的排列数量
 * - 如果第 n 位不使用，那么我们直接从 n - 1 的位置转移过来
 * - 否则，那将 n 和前 n - 1 中的一个位置交换
 * 综上所述，可得 f[n][j] = f[n - 1][j] + (n - 1) * f[n - 1][j - 1]
 * 
 * 因为我们只进行 k 次交换，所以最多只能交换 2k 个位置
 * 我们可以每次从 n 中选出一些要交换的位置，然后对于这些位置求方案数
 * 上面的 f[n][j] 因为包含了某些原位的情况，所以不能直接用作方案数
 * 那么，我们假定 ff[n][j] 表示了 n 个位置全部错位的，j 次复位的排列数量
 * 那么，可以使用类似错排公式的包含-移除方法，将 f 固定位数得到 ff
 * 这样，我们就可以使用 O(k³) 求出的 nCr 和 ff 求出这个问题的答案了
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

const int N = 500;
const int mod = 1e9 + 7;
longs inv[N], c[N][N], f[N][N];

void initInverse(int n, longs p) {
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
    inv[0] = 0;
}

longs nCr(int n, int r) {
    longs ret = 1;
    for (int i = n - r + 1; i <= n; ++ i)
        ret = ret * i % mod;
    for (int i = 1; i <= r; ++ i)
        ret = ret * inv[i] % mod;
    return ret;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);
    
    int n = $.nextInt(), k = $.nextInt();
    c[0][0] = 1;
    for (int i = 1; i <= 2 * k; ++ i) {
        f[i][0] = 1, c[i][0] = 1;
        for (int j = 1; j <= 2 * k; ++ j) {
            f[i][j] = (f[i - 1][j] + (i - 1) * f[i - 1][j - 1]) % mod;
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
        }
    }
    initInverse(2 * k, mod);
    longs ans[] = {1, 0};
    vector<int> out;
    for (int j = 1; j <= k; ++ j) {
        const auto lim = min(n, 2 * j);
        for (int i = 1; i <= lim; ++ i) {
            longs cnt = 0, fix, fl;
            for (fix = 0, fl = 1; fix <= i; ++ fix, fl = -fl) {
                cnt = cnt + fl * c[i][fix] * f[i - fix][j] % mod;
                do cnt = (cnt + mod) % mod; while (cnt < 0);
            }
            ans[j % 2] = (ans[j % 2] + nCr(n, i) * cnt) % mod;
        }
        out.push_back((int) ans[j % 2]);
    }
    $.putArray(out.begin(), out.end());

    return 0;
}