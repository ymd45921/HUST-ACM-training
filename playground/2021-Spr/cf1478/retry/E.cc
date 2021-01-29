/**
 *
 * 使用了新鲜出炉的珂朵莉树板子：
 * - 首先，虽然顺着推有很多说法，但是倒着推只有一种情况
 * - 因此，只需要找一个差不多得了的数据结构就行
 * 能看到的一大堆 assign 操作，那珂朵莉树就得了（
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

const int N = 2e5 + 5;
char s[N], t[N];

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
};

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    vector<pair<int, int>> opt;
    while (T --)
    {
        int n = scanner.nextInt(),
            q = scanner.nextInt();
        scanner(s + 1, t + 1);
        chtholly odt(n + 1, 0);
        int last = 0, ll = 0, rr;
        for (rr = 1; rr <= n; ++ rr)
            if (t[rr] - '0' != last)
            {
                odt.assign(ll, rr - 1, last);
                last = t[rr] - '0', ll = rr;
            }
        odt.assign(ll, n, last);
        opt.clear();
        while (q --)
        {
            scanner(ll, rr);
            opt.emplace_back(ll, rr);
        }
        reverse(opt.begin(), opt.end());
        bool ok = true;
        for (auto [l, r] : opt)
        {
            int cnt[2] = {0, 0};
            odt.iterate(l, r, [&](auto it)
            {auto [_l, _r, v] = *it; cnt[v] += _r - _l + 1;});
            if (cnt[0] == cnt[1]) {ok = false; break;}
            else if (cnt[0] < cnt[1]) odt.assign(l, r, 1);
            else odt.assign(l, r, 0);
        }
        if (!ok) { puts("NO"); continue; }
        for (int i = 1; i <= n; ++ i)
            if (odt.at(i) != s[i] - '0')
            {ok = false; break;}
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
