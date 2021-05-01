/**
 *
 * 这 nm 也能倍增？
 *
 * 考虑前面推导出的，对于长度为 n 的，交换 j 次复位的方案数 f[n][j]
 * 考虑它的转移方程：如果第 n 位错位了，那么引入了 (n - 1)，且 j 减少
 * 如果这样的话，可以认为 f[n][j] 就是所有大小为 j 的 [0, n - 1] 的子集乘积和
 * 这个子集中包含的数字某种程度上（0-index）就是 n 个位置中引入错位的位置
 * 要区别这个和错位的位置：根据转移，我们是在交换 i 和小于 i 的某位置后引入 *i 的
 * 所以每次引入 i 只是可能和前面的 i - 1 个位置发生交换，不会被重复计数
 *
 * 那么，假设先固定 j，然后考虑使用 f[n][] 来求 f[2n][]；显然，前者已计算：
 * - 我们选择了 l 个来自于 [0, n - 1] 和 j - l 个来自于 [n, 2n - 1] 的位置
 * - 较小的 l 个位置很简单，就是已经计算过的 f[][l]
 * - 较大的 j - l 个位置，可以看成从 [0, n - 1] 中选择，但是每个位置都 +n
 * - 将这样的乘积式子化简，会发现每一项都有 j - l 个部分相乘
 * - 其中每一个部分，要不是 [0, n - 1] 的位置 i，要不是 +n 部件，很像二项式
 * - 那么对于某一项，假设它包含了 m 个位置，那显然可以由 f[][m] 转移而来
 * 综上所述，我们就可以完成第二个部分的求解，从而向 f[2n][] 转移；
 * 因此，实现过程中只要维护当前长度 n 对于全部有效 j 的 f[n][] 即可
 * 
 * 因为我们要使用朴素的递推和上述的倍增从 1 开始转移到 n；
 * 那么这个过程很显然需要按照二进制拆分 n，按位进行复原重构 n 的过程中转移；
 *
 * 关于 30 - __builtin_clz(n)：返回了 int 类型的 n 的最高位 1 的下一个位置
 * 显然，31 - __builtin_clz(n) 返回了 int 类型的 n 的最高位 1 的下标
 * 代码中的使用是用来从高位到低位重建 cur = n 的： 按位进行翻倍递增
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
longs inv[N], f[N], big[N], np[N], tmp[N];

void initInverse(int n, longs p) {
    inv[0] = inv[1] = 1;
    for(int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
    inv[0] = 0;
}

longs nCr(longs n, longs r) {
    longs ret = 1;
    for (auto i = n - r + 1; i <= n; ++ i)
        ret = ret * i % mod;
    for (int i = 1; i <= r; ++ i)
        ret = ret * inv[i] % mod;
    return ret;
}

void calculate(int k, longs now) {
    memset(big, 0, sizeof(longs) * (k + 1));
    memset(np, 0, sizeof(longs) * (k + 1));
    np[0] = 1;
    for (int i = 1; i <= k; ++ i)
        np[i] = now * np[i - 1] % mod;
    const auto lim = min((longs)k, now);
    for (int i = 0; i <= lim; ++ i)
        for (int j = 0; j <= i; ++ j) {
            auto t = nCr(now - j, i - j) * f[j] % mod * np[i - j] % mod;
            big[i] = (big[i] + t) % mod;
        }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int n = $.nextInt(), k = $.nextInt();
    const bitset<64> nn = n;
    initInverse(N - 1, mod);
    longs now = f[0] = 1;
    for (int i = 30 - __builtin_clz(n); i >= 0; -- i) {
        calculate(k, now);
        memset(tmp, 0, sizeof(longs) * (k + 1));
        for (int s = 0; s <= k; ++ s)
            for (int b = 0; b <= k; ++ b)
                if (s + b <= k)
                    tmp[s + b] = (tmp[s + b] + f[s] * big[b]) % mod;
                else break;
        memcpy(f, tmp, sizeof(longs) * (k + 1));
        now *= 2;
        if (nn.test(i)) {
            memset(tmp, 0, sizeof(longs) * (k + 1));
            tmp[0] = 1;
            for (int j = 1; j <= k; ++ j)
                tmp[j] = (f[j] + now * f[j - 1]) % mod;
            memcpy(f, tmp, sizeof(longs) * (k + 1));
            ++ now;
        }
    }
    longs ans[] = {1, 0};
    vector<int> out;
    for (int j = 1; j <= k; ++ j) {
        ans[j % 2] = (ans[j % 2] + f[j]) % mod;
        out.push_back((int) ans[j % 2]);
    }
    $.putArray(out.begin(), out.end());

    return 0;
}