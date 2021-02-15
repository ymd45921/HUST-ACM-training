/**
 *
 * 在莫队的启发下弃暗投明，想到了线段树做法
 * 但是我实在是太不会写线段树了orz（
 * 
 * 原来黄名人打 div2 都是一小时五个题的🐎==
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

const int N = 150000 + 5;
const int inf = 0x3f3f3f3f;
pair<int, int> a[N], b[N], c[N], d[N];
unordered_set<int> ab[N], bc[N], cd[N];

template <class T>
class seg_tree
{
    using merge_t = function<T(T&, T&)>;
    int siz;
    vector<T> t;
    merge_t merge;
    T init;

    void fix(int id)
    {t[id] = merge(t[id * 2 + 1], t[id * 2 + 2]);}

    void build(int id, int l, int r)
    {
        if (l + 1 == r) { t[id] = init; return; }
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m);
        build(id * 2 + 2, m, r);
        fix(id);
    }

    void update(int id, int l, int r, int pos, T val)
    {
        if (l + 1 == r)
        {
            t[id] = merge(t[id], val);
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) update(id * 2 + 1, l, m, pos, val);
        else update(id * 2 + 2, m, r, pos, val);
        fix(id);
    }

    T query(int id, int l, int r, int ll, int rr)
    {
        if (ll >= rr) return init;
        else if (ll == l && rr == r) return t[id];
        int m = (l + r) / 2;
        auto lv = query(id * 2 + 1, l, m, ll, min(rr, m));
        auto rv = query(id * 2 + 2, m, r, max(m, ll), rr);
        return merge(lv, rv);
    }

public:
    explicit seg_tree(int n = 0, T default_v = 0,
                      merge_t m = [](T &a, T &b){return max(a, b);})
            : siz(n), init(default_v), merge(std::move(m)) {t.resize(4 * n);}

    void resize(int n) {siz = n; t.resize(4 * n);}

    void build() {return build(0, 0, siz + 1);}

    void update(int pos, T val) {update(0, 0, siz + 1, pos, val);}

    T query(int ll, int rr) {return query(0, 0, siz + 1, ll, rr);}
};

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n1, n2, n3, n4;
    scanner(n1, n2, n3, n4);
    for (int i = 1; i <= n1; ++ i)
        a[i].first = scanner.nextInt(),
        a[i].second = i;
    for (int i = 1; i <= n2; ++ i)
        b[i].first = scanner.nextInt(),
        b[i].second = i;
    for (int i = 1; i <= n3; ++ i)
        c[i].first = scanner.nextInt(),
        c[i].second = i;
    for (int i = 1; i <= n4; ++ i)
        d[i].first = scanner.nextInt(),
        d[i].second = i;
    int m1, m2, m3, x, y;
    scanner(m1);
    for (int i = 1; i <= m1; ++ i)
        scanner(x, y),
        ab[x].insert(y);
    scanner(m2);
    for (int i = 1; i <= m2; ++ i)
        scanner(x, y),
        bc[x].insert(y);
    scanner(m3);
    for (int i = 1; i <= m3; ++ i)
        scanner(x, y),
        cd[x].insert(y);
    using bcd = tuple<int, int, int>;
    seg_tree<bcd> t(n4 + 1, make_tuple(0, 0, 0),
                    [](bcd &a, bcd &b)
                    {
        return make_tuple(min(get<0>(a), get<0>(b)),
                          min(get<1>(a), get<1>(b)),
                          min(get<2>(a), get<2>(b)));
                    });

    return 0;
}