/**
 *
 * 为什么数组空间没开够是 T 而不是 RE 啊
 * 我不能接受——————
 * 
 * 总之这就是一个莫队算法的板子了；
 * 
 * C++ 学习笔记：
 * - bind 绑定的返回值是 _Bind，不能被设置为 const
 * - bind 中传递引用必须使用 ref() 包裹才行
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
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
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

struct fast_read
{
    template <class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;

#define $$ fastRead,
#define int$(...) int __VA_ARGS__; $$ __VA_ARGS__
#define i64$(...) longs __VA_ARGS__; $$ __VA_ARGS__
#define lll$(...) lll __VA_ARGS__; $$ __VA_ARGS__

const int N = 3e5 + 5;
int a[N];

namespace MO
{
    int block_size = 1;

    struct query 
    {
        int l, r, id;

        query() = default;
        query(int l, int r, int id) : l(l), r(r), id(id) {}

        bool operator <(const query &rhs) const
        {
            if (l / block_size == 
                rhs.l / block_size)
                return r < rhs.r;
            else return l < rhs.l;
        }
    };

    vector<query> req;
    vector<int> ans;
    int cnt[N], tim[N];

    void step(int pos, int sig, int &now)
    {
        auto &times = tim[a[pos]];
        if (times >= 0) -- cnt[times];
        times += sig;
        if (times >= 0) ++ cnt[times];
        if (sig > 0) maximize(now, times);
        else while (!cnt[now]) -- now;
    }

    void init(int n, int m) 
    {
        ans.resize(m + 1);
        block_size = (int) ceil(sqrt(n));
        stable_sort(req.begin(), req.end());
    }

    void solve(int n, int m)
    {
        int l = 0, r = 0, tmp = 0;
        using namespace placeholders;
        auto increase = bind(step, _1, +1, ref(tmp));
        auto decrease = bind(step, _1, -1, ref(tmp));
        for (auto [ql, qr, qid] : req)
        {
            while (ql < l) increase(-- l);
            while (qr > r) increase(++ r);
            while (ql > l) decrease(l ++);
            while (qr < r) decrease(r --);
            const auto len = qr - ql + 1;
            ans[qid] = max(1, 2 * tmp - len);
        }
    }

    void run(int n, int m) {init(n, m), solve(n, m);}
}

template <class T, class Typ>
void discretize(T first, T last, Typ start = 0)
{
    set<Typ> sorter;
    map<Typ, Typ> map;
    for (T cur = first; cur != last; ++ cur) 
        sorter.insert(*cur);
    for (auto ii : sorter) map[ii] = start ++;
    for (T cur = first; cur != last; ++ cur) 
        *cur = map[*cur];
}

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
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    // discretize(a + 1, a + 1 + n, 1);
    for (int i = 1; i <= m; ++ i)
    {
        int l = scanner.nextInt(),
            r = scanner.nextInt();
        MO::req.emplace_back(l, r, i);
    }
    MO::run(n, m);
    for (int i = 1; i <= m; ++ i)
        println(MO::ans[i]);
    return 0;
}