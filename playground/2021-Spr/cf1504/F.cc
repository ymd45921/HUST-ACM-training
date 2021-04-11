/**
 *
 * 不得不说这个题目确实是远超出了我的知识水平……
 * 真的是看着题解都毫无想法，但是也真的可以做（
 *
 * 首先需要认识到这些东西：
 * - 一张牌的两面必须一个属于 [1, n] 另一个属于 [n+1, 2n]，否则无解
 *   - 假设一张牌的两面都属于 [1, n]，分别为 x, y，有 x < y
 *   - 假设较小的一面 x 在正面，较大的一面 y 在背面
 *   - 那么，最多有 x-1 张牌在左边，相应的 y-x+1 张牌在右边
 *   - 也就是说，这副牌最多有 y-1 张，而 y <= n
 * - 对于任何一副满足上述限制的牌，按照正面递增排序，记背面为 f[i]
 *   - 对于 f[i] 构成的序列，必须要可以拆分成两个递减的子序列才可以满足
 *     - 正确性？将其中的一个子序列的牌全部翻面倒序，就可以作为序列后缀
 *     - 必要性？分解成三个递减子序列，那么前两个合并后无法并入第三个
 *     - 至于怎么想到这个，我也没什么想法，，不然我也不会补这个题目了
 *   - 因为并不是所有的手牌都是初始较小面朝上的，所以需要先行翻转
 *   - 划分成两个子序列之后，只需要将其中翻转成本较小的一组翻转即可
 * - 其中，能达到最小翻转次数的构造方法是将原问题划分成更小的问题
 *   - 显然，划分需要满足一些条件，否则三个递减子序列也有办法拼起来
 *   - 一般来说，对于划分成两个子序列的问题，往往有多种划分方法
 *     - 显然，划分方法的不同也会影响到最终我们的翻转次数
 *     - 因为不同的划分分成的组中，有的翻转是可以通过分到另一组来避免的
 *     - 因此，不难想到，只要将划分问题的粒度降到最低，就可以保证最小
 *     - 划分子问题之后不可避免要合并为原来的问题，因此需要考虑
 *   - 综上所述，我们考虑这种划分方法：
 *     - 对于上述的每一个索引（正面值）i，满足了前缀最小大于后缀最大则划分
 *     - 为什么这样的划分是符合题目要求（即可以合并为大问题）呢
 *       - 首先对于每一个子问题，分解成两个子序列后合并得到的大概是下面：
 *         - 未翻转的部分，递增的正面小于 n，递减的背面大于 n
 *         - 翻转的部分，vice versa
 *       - 原序列正面已经桶排序，递增且总是为 1 ~ n
 *         - 如果背面有前缀最小大于后缀最大，那么前后面的翻转也保持
 *         - 保证了前缀翻转后的部分总是完全大于后缀翻转的部分
 *         - 是充分的条件（因为翻转的未必是极值，所以保有空间）
 *     - 为什么这样做可以保证翻转的次数最小呢
 *       - 首先，每一个子问题都已经是最小粒度，可以避免跨子问题的冗余翻转
 *       - 那么，子问题内部为什么保证了划分一定是最优的呢
 *         - 前缀的最小值只会不断变小，因此，导致了划分的只可能是最大值的加入
 *         - 这样的话，因为之前没有划分，所以最大值一定是大于前缀最小值的
 *         - 所以，这一定形成了一个逆序对；而刚形成了逆序对就进行划分是唯一的
 *         - 如果这个逆序对不是唯一的逆序对，那么就无法划分
 *       - 综上所述，总是在逆序对形成且可以合并的事后划分，保证了必要性
 *       - 此时，如果之前也产生了其他的逆序对，那么会无法划分成两个递减子序列
 *       - 否则，形成的划分是唯一的：刚加入的逆序大值和之前的递减子序列
 *     - 综上所述，这样可以得到这个题目的构造方法，时间复杂度是 O(n)
 * 其实，这个题远没有我第一次看到的时候那么的不可做，只是需要正确的考虑（
 * 当然，朴素的考虑也没有可以变成这种精巧的讨论的感觉，只能说很巧妙了（
 * 甚至，这还是一个 2-SAT tag 的题目，只是我已经完全不会这个玩意了（
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
    cquery &operator()(char *x, Ts &&... y) {
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

    template<class T>
    T next() {
        T ret;
        (*this)(ret);
        return ret;
    }

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
        return write(stdout, x, '\n'), *this;
    }

    template<class T>
    cquery &log(const T &&x) {
        return write(stderr, x, '\n'), *this;
    }

    template<class T, class ...Ts>
    cquery &log(const T &x, Ts ...xs) {
        write(stderr, x, ' '), put(xs...);
        return *this;
    }

    template<class T, class ...Ts>
    cquery &log(const T &&x, Ts ...xs) {
        write(stderr, x, ' '), put(xs...);
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
    void trace(const char *name, T &&value) { write(stderr, name, " = ", value); }

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

const int N = 2e5 + 5;
pair<int, int> a[N];
bitset<N> rev;
int f[N], suf[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int n = $.nextInt();
    $.nextArray(a + 1, a + 1 + n);
    bool legal = true;
    for (int i = 1; i <= n; ++i) {
        if (a[i].first > a[i].second) {
            swap(a[i].first, a[i].second);
            rev.set(a[i].first);
        }
        if (a[i].first > n || a[i].second <= n) {
            legal = false;
            break;
        } else f[a[i].first] = a[i].second;
    }
    if (!legal) {
        output, -1, endl;
        return 0;
    } else {
        suf[n + 1] = -1;
        for (int i = n; i >= 1; -- i)
            suf[i] = max(f[i], suf[i + 1]);
        int pref = 0x3f3f3f3f;
        int cosA = 0, cosB = 0, ans = 0;
        vector<int> seqA, seqB;
        for (int i = 1; i <= n; ++ i) {
            minimize(pref, f[i]);
            if (seqA.empty() || seqA.back() > f[i])
                seqA.push_back(f[i]), cosA += rev[i];
            else if (seqB.empty() || seqB.back() > f[i])
                seqB.push_back(f[i]), cosB += rev[i];
            else {
                output, -1, endl;
                return 0;
            }
            if (pref > suf[i + 1]) {
                int sizA = (int)seqA.size(),
                    sizB = (int)seqB.size();
                ans += min(cosA + sizB - cosB, cosB + sizA - cosA);
                cosA = cosB = 0;
                seqA.clear(), seqB.clear();
            }
        }
        output, ans, endl;
    }
    return 0;
}