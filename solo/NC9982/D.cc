/**
 *
 * 不对劲，珂朵莉树应该是被卡的铁死，大概需要动态开点线段树吧（
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
void print(string &s) {printf(s.c_str());}
void print(const char *s) {printf(s);}
void print(char *s) {printf(s);}
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

const int N = 1e5 + 5;
map<int, int> cnt;

template <class value>
class chtholly
{
    struct node
    {
        unsigned l{}, r{};
        mutable value v;

        node() = default;
        node(unsigned l, unsigned r, value v)
                : l(l), r(r), v(v) {}
        bool operator<(const node &rhs)
        const {return l < rhs.l;}
    };

    set<node> tree;
    unsigned n;

    using iterator = typename set<node>::iterator;
    using travel_t = function<void(iterator)>;

    iterator split(unsigned index)
    {
        if (index >= n) return tree.end();
        auto it = -- tree.upper_bound({index, 0, 0});
        if (it->l == index) return it;
        auto [l, r, v] = *it;
        tree.erase(it);
        tree.insert({l, index - 1, v});
        return tree.insert({index, r, v}).first;
    }

public:
    explicit chtholly(int siz, value init = 0) : n(siz)
    {tree.insert({0, siz - 1u, init});}

    void clear() {tree.clear(); tree.insert({0, n - 1u, 0});}

    void resize(int siz) {n = siz; clear();}

    value at(unsigned index)
    {return (-- tree.upper_bound({index, 0, 0}))->v;}

    void assign(unsigned l, unsigned r, value v)
    {
        auto rr = split(r + 1), ll = split(l);
        tree.erase(ll, rr);
        tree.insert({l, r, v});
    }

    void iterate(unsigned l, unsigned r, const travel_t &it)
    {
        auto rr = split(r + 1), ll = split(l);
        for (; ll != rr; ++ ll) it(ll);
    }

    void increase(unsigned l, unsigned r)
    {
        auto rr = split(r + 1), ll = split(l);
        for (; ll != rr; ++ ll) ++ ll->v;
    }

    void count(unsigned l, unsigned r)
    {
        auto rr = split(r + 1), ll = split(l);
        for (; ll != rr; ++ ll) cnt[ll->v] += ll->r - ll->l + 1;
    }
};

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    chtholly odt(n + 1, 0);
    for (int ll, rr; m --;)
    {
        scanner(ll, rr);
//        odt.iterate(ll, rr, [](auto it)
//        {auto &[l, r, v] = *it; ++ v;});
        odt.increase(ll, rr);
    }
//    odt.iterate(1, n, [&](auto it)
//    {auto [l, r, v] = *it; cnt[v] += r - l + 1;});
    odt.count(1, n);
    if (!cnt.count(1)) cnt[1] = 0;
    int gold = 1, sliver = 1, bronze = 1;
    int t1 = n / 10 + bool(n % 10),
        t2 = n / 4 + bool(n % 4),
        t3 = n / 2 + bool(n % 2);
    int last = 0;
    for (auto it = cnt.rbegin();
         it != cnt.rend(); ++ it)
    {
        auto &[i, num] = *it;
        num += last, last = num;
        if (num >= t1) maximize(gold, i);
        if (num >= t2) maximize(sliver, i);
        if (num >= t3) maximize(bronze, i);
    }
    print(cnt[gold], ' ',
          cnt[sliver] - cnt[gold], ' ',
          cnt[bronze] - cnt[sliver]);
    return 0;
}