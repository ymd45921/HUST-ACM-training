/**
 * 
 * 当心函数式编程！意外的捕获行为使我调了一整天
 * 指 [..., &getter = ...] 按值捕获原来是静态的吗
 * 可能对于按值捕获的理解需要更进一步才行（
 * 
 * 如果暴力的去考虑这个问题，就是更新之后每次都按照顺序遍历
 * 按照排序后的顺序加入背包，如果不能加入就向下移位
 * 直到遍历完整个宝石阵列，就可以将所有可以加入的宝石贪心加入
 * 
 * 假设我们的背包现在还有 c 的容量，满足 c ∈ [2^(m - 1), 2^m)
 * 假设我们每次只考虑重量小于 2^k 的钻石，其中：
 * - 重量 w <= 2^(k - 1) 的宝石是轻的
 * - 重量 w ∈ [2^(k - 1), 2^k) 的宝石是重的
 * 那么我们先从 k = m + 1 开始考虑：
 * - 显然，我们不可能包含任何重宝石；任何一颗都比我们的背包大
 * - 那么，我们唯一可以考虑的就是轻宝石：
 *   - 如果对于一个区间的轻宝石，它们重量和可以塞进背包，那就塞
 *   - 否则说明轻宝石中也有部分宝石无法加入，我们先减少 k
 * - 如果此时，整个区间中存在一个包含新的重宝石的前缀，那么：
 *   - 如果这个前缀可以被包含，那么可能前缀后还有空间，递归：
 *   - 此时，整个前缀转移来源的几个子区间一定都可以被选中
 *   - 那么，在这个前缀右侧的区间，会成为全新的问题，当然可解
 *   - 否则，这个区间的所有新重宝石都不可能包含了
 *     - 因为维护的时候确保了靠左边能拿的宝石都拿了
 *     - 维护确保了这是这个区间按照顺序拿一颗重宝石的最轻情况
 *     - 甚至实际上这种情况都未必正确，只判明重宝石可以考虑
 *   - 想象一下，如果这重宝石可以拿，可能是以下的情景：
 *     - 刚刚好可以拿最小值，按照顺序拿了就是拿了
 *     - 还有更多的空间，那么考虑出现在这个位置之前的重宝石
 *       - 它们一定是从某个更小的区间转移上来，但是最后又被舍弃了
 *       - 递归子区间，先处理左边，就可以保证按照顺序拿取
 *     - 这样，即使到了拿不到的区间，拿不到就算了（
 *   - 如果重宝石不可能包含，那么考虑降一级后的轻宝石：
 *     - 如果它们都可以加入背包，那么就加入吧，没有更好的说法了
 *     - 否则，考虑递归，有些子区间可能还要继续降级考虑（
 *   - 因此，这样的做法保证了可以得到正确的答案
 * - 综上所述，我们就得到了一种利用维护的数据递归的求解的方法；
 * 这已经和上面最开始最开始的时候说的那个暴力的方法大不相同了
 * 那么我们来考虑以下为什么这样会快很多呢？
 * - 首先，我们直接利用维护的数据可以快速对于背包可装的进行试探
 * - 背包的容量总是在减少，在最高位不变的情况下只能塞入一颗重宝石
 * - 因此，考虑低一位的轻宝石之后，最多只会再多来一颗同位的重宝石
 * - 所以，通过区间最低的重宝石重量可以判别是否可能有重宝石
 *   - 有，那么是递归向上转移的，继续拆分找到那个可以完全加入的区间就好
 *   - 无，那么最多就是满编轻宝石，不能的话还是得拆分找子区间的情况
 * - 如果一层重宝石不可能了，根据需要可以向下减小位数
 * 因此，基本就是在每一层都能完成对于当前层的需求的试探和求解
 * 而这个层数是极其有限的，也就是最开始说的那个 log c
 * 
 * 对于代码的解释结束了，再尝试着解释一下官方题解吧：
 * - 同样是对于一个选择的 k，排序之后考虑轻重宝石；现在对于区间
 * - 因为总是在贪心的买入，所以袋子的可用空间只会不断地减少
 * - 考虑到它的空间减少到 2^(k - 1) 之下的那个节点：
 *   - 在这个节点之前，它可以拿任何的轻宝石，只要容量没有掉下去
 *   - 当然，因为可用空间大于重宝石要求，所以也可以拿重宝石（显然，最多一颗
 *   - 在这个节点之后，它不可能拿任何的重宝石，甚至轻宝石都不一定
 * - 此时，原来的轻宝石就可以看作降级后的重宝石，可以继续作为子问题求解
 * 那么，问题就在于对于每个子问题，这颗重宝石怎么拿，在哪里拿
 * 我们维护了区间的重量最小的前缀轻宝石 + 重宝石的组合的重量，用来判明可能
 * - 如果可能，那么就递归地判断最先出现的可拿的重宝石位置
 * - 否则，就降级标准线继续判断可能性
 * 对于这样做的快速性和合理性进行简单的说明：
 * 在划定了合理的 k 之后，宝石被分为轻重两种，当然，还有超重的，完全不考虑
 * 因为是贪心地从左到右拿，所以只要还能维持标准 k，轻宝石是遇到了就拿
 * 因为数值关系的原因，重宝石最多也只会拿一颗；如果不能拿，会被跳过去
 * 所以对于区间，维护对于 k 的所有的轻宝石重量，设法考虑重宝石就可以了
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

template<class T>
class fp_seg_tree {

    using merge_method = function<void(T &, T &, T &, int, int)>;
    using build_method = function<void(T &, int)>;

    int siz;
    vector<T> t;
    merge_method merge;
    build_method init;

    inline void push_up(int id, int l, int r) {
        merge(t[id], t[id * 2 + 1], t[id * 2 + 2], l, r);
    }

    void build(int id, int l, int r, build_method mk) {
        if (l + 1 == r) return mk(t[id], l);
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m, mk);
        build(id * 2 + 2, m, r, mk);
        push_up(id, l, r);
    }

    void build(int id, int l, int r, int ll, int rr) {
        if (ll >= r || rr <= l) return;
        if (l + 1 == r) return init(t[id], l);
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m, ll, rr);
        build(id * 2 + 2, m, r, ll, rr);
        push_up(id, l, r);
    }

    void update(int id, int l, int r, int pos, T &val) {
        if (l + 1 == r) {
            t[id] = val;
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) update(id * 2 + 1, l, m, pos, val);
        else update(id * 2 + 2, m, r, pos, val);
        push_up(id, l, r);
    }

    void re_init(int id, int l, int r, int pos) {
        if (l + 1 == r) return init(t[id], l);
        int m = (l + r) / 2;
        if (pos < m) re_init(id * 2 + 1, l, m, pos);
        else re_init(id * 2 + 2, m, r, pos);
        push_up(id, l, r);
    }

    T query(int id, int l, int r, int ll, int rr) {
        if (ll >= rr) return T{};
        else if (ll == l && rr == r) return t[id];
        int m = (l + r) / 2;
        auto lv = query(id * 2 + 1, l, m, ll, min(rr, m));
        auto rv = query(id * 2 + 2, m, r, max(m, ll), rr);
        T ret{};
        return merge(ret, lv, rv, ll, rr), ret;
    }

public:
    explicit fp_seg_tree(int n, merge_method m, build_method b)
            : siz(n), merge(std::move(m)), init(std::move(b))
    { t.resize(4 * n); }

    void resize(int n) {
        siz = n;
        t.resize(4 * n);
    }

    void build(build_method mk) { return build(0, 0, siz, mk); }

    void update(int pos, T val) { update(0, 0, siz, pos, val); }

    T query(int ll, int rr) { return query(0, 0, siz, ll, rr); }

    void re_init(int pos) { re_init(0, 0, siz, pos); }

    void re_init(int l, int r) { build(0, 0, siz, l, r); }

    size_t size() { return siz; }

    void build() { build(0, 0, siz, 0, siz); }

    auto get() { return make_tuple(cref(t), cref(init), cref(merge)); }

#ifdef fp_seg_tree_experimental
    template<typename resT>
    using query_method = function<resT(int, int, int, int, int)>;

    template<typename res>
    res query(int ll, int rr, query_method<res> sub) {
        return sub(0, 0, siz, ll, rr);
    }
#endif
};

template <unsigned siz>
struct node {
    using element = array<longs, siz>;
    element wSumL, vSumL, wOne, vOne;
};

const int N = 2e5 + 5;
const longs inf = 1e18 + 7;
using diamond = tuple<int, int, int, longs>;
diamond a[N];
int id[N];

template <unsigned siz>
void getNode(node<siz> &out, int i) {
    const auto &[w, v, ii, cnt] = a[i];
    for (uint k = 1; k < siz; ++ k) {
        const auto heavy = w < (1u << k);
        const auto light = 1u << (k - 1);
        out.wSumL[k] = out.vSumL[k] = 0;
        out.vOne[k] = out.wOne[k] = inf;
        if (w < light) {
            out.wSumL[k] = cnt * w, out.vSumL[k] = cnt * v;
        } else if (heavy && cnt)
            out.vOne[k] = v, out.wOne[k] = w;
    }
}

template <unsigned siz>
void mergeNode(node<siz> &now, node<siz> &ll,
               node<siz> &rr, int l, int r) {
    for (uint k = 1; k < siz; ++ k) {
        now.wSumL[k] = ll.wSumL[k] + rr.wSumL[k];
        now.vSumL[k] = ll.vSumL[k] + rr.vSumL[k];
        if (ll.wOne[k] < ll.wSumL[k] + rr.wOne[k]) {
            now.wOne[k] = ll.wOne[k], now.vOne[k] = ll.vOne[k];
        } else {
            now.wOne[k] = ll.wSumL[k] + rr.wOne[k];
            now.vOne[k] = ll.vSumL[k] + rr.vOne[k];
        }
    }
}

size_t clz(longs x) {
    if (!x) return -1;
    return 64 - __builtin_clzll(x);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(null), cout.tie(null);

    int n, q, k, d;
    longs c;
    $(n, q);
    for (int i = 0; i < n; ++i) {
        auto &[w, v, id, cnt] = a[i];
        $(cnt, w, v), id = i + 1;
    }
    sort(a, a + n, [](auto &a, auto &b) {
        const auto &[aw, av, aid, ac] = a;
        const auto &[bw, bv, bid, bc] = b;
        return av == bv ? aw < bw : av > bv;
    });
    for (int i = 0; i < n; ++i) id[get<2>(a[i])] = i;
    fp_seg_tree<node<20>> t(n, mergeNode<20>, getNode<20>);
    t.build();
    using fp_query_t = function<longs(int, int, int)>;
    const fp_query_t solve = [&, &getter = get<0>(t.get())]
            (int pos, int l, int r) -> longs {
        if (l >= r) return 0;
        else if (l + 1 == r) {
            auto [w, v, i, cnt] = a[l];
            auto t = min(cnt, c / w);
            c -= t * w;
            return t * v;
        } else {
            auto m = min(19ull, clz(c) + 1);
            auto &ii = getter[pos];
            if (ii.wSumL[m] <= c) {
                c -= ii.wSumL[m];
                return ii.vSumL[m];
            } else if (ii.wOne[m - 1] > c &&
                       ii.wSumL[m - 1] <= c) {
                c -= ii.wSumL[m - 1];
                return ii.vSumL[m - 1];
            } else {
                auto mid = (l + r) / 2;
                return solve(pos * 2 + 1, l, mid) +
                       solve(pos * 2 + 2, mid, r);
            }
        }
    };
    const auto query = [solve, n] { return solve(0, 0, n); };
    while (q--)
        switch ($.nextInt()) {
            case 1:
                $(k, d);
                get<3>(a[id[d]]) += k;
                t.re_init(id[d], id[d] + 1);
                break;
            case 2:
                $(k, d);
                get<3>(a[id[d]]) -= k;
                t.re_init(id[d], id[d] + 1);
                break;
            case 3:
                $(c).put(query());
                break;
            default:
                break;
        }

    return 0;
}
