/**
 *
 * 分块 + 二分
 * 直接给爷写吐了
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
    template<class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;
#define $$ fastRead,

const int N = 1e5 + 5;
int A[N];

struct partial
{
    int siz, apply;
    map<int, int> cnt;
    vector<int> arr;
    bool lazy = false;
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
    for (int i = 0; i < n; ++ i)
        A[i] = scanner.nextInt();
    int partSiz = sqrt(n), partCnt = (n + partSiz - 1) / partSiz;
    vector<partial> part(partCnt);
    const auto applyLazy =
    [&](partial &This)
    {
        if (!This.lazy) return;
        for (auto &i : This.arr)
            minimize(i, This.apply);
        This.lazy = false;
    };
    const auto partition =
    [&](int l, int r)
    {
        int ll = l / partSiz, rr = r / partSiz;
        int lb = -1, rb = -1;
        if (l % partSiz) lb = ll ++;
        if (r + 1 == n);
        else if (r % partSiz != partSiz) rb = rr --;
        return make_tuple(ll, rr, lb, rb);
    };
    const auto update =
    [&](int l, int r, int x)
    {
        auto [ll, rr, lb, rb] = partition(l, r);
        const auto bruteUpdate =
        [&](partial &This, int i)
        {
            if (This.arr[i] <= x) return;
            if (!-- This.cnt[This.arr[i]])
                This.cnt.erase(This.arr[i]);
            ++ This.cnt[x], This.arr[i] = x;
        };
        for (int ii = ll; ii <= rr; ++ ii)
        {
            auto &This = part[ii];
            auto lit = This.cnt.upper_bound(x);
            if (lit != This.cnt.end())
            {
                This.lazy = true, This.apply = x;
                int modifyCnt = 0;
                for (auto it = lit; it != This.cnt.end(); ++ it)
                    modifyCnt += it->second;
                This.cnt.erase(lit, This.cnt.end());
                This.cnt[x] += modifyCnt;
            }
        }
        if (lb > -1)
        {
            auto &This = part[lb];
            applyLazy(This);
            for (int i = l % partSiz; i < This.siz; ++ i)
                bruteUpdate(This, i);
        }
        if (rb > -1)
        {
            auto &This = part[rb];
            applyLazy(This);
            const auto lim = r % partSiz;
            for (int i = 0; i < lim; ++ i)
                bruteUpdate(This, i);
        }
    };
    const auto query =
    [&](int l, int r, int k) -> int
    {
        auto [ll, rr, lb, rb] = partition(l, r);
        int _l = 1, _r = n;
        while (_l <= _r)
        {
            auto mid = (_l + _r) / 2;
            int big = 0, same = 0;
            for (int i = ll; i <= rr; ++ i)
            {
                auto &This = part[i];
                auto ub = This.cnt.upper_bound(mid);
                auto lb = This.cnt.lower_bound(mid);
                auto end = This.cnt.end();
                for (auto it = lb; it != ub; ++ it)
                    same += it->second;
                for (auto it = ub; it != end; ++ it)
                    big += it->second;
            }
            if (lb > -1)
            {
                auto &This = part[lb];
                applyLazy(This);
                for (int i = l % partSiz; i < This.siz; ++ i)
                    if (This.arr[i] == mid) ++ same;
                    else if (This.arr[i] > mid) ++ big;
            }
            if (rb > -1)
            {
                auto &This = part[rb];
                applyLazy(This);
                const auto lim = r % partSiz;
                for (int i = 0; i < lim; ++ i)
                    if (This.arr[i] == mid) ++ same;
                    else if (This.arr[i] > mid) ++ big;
            }
            if (big < k && big + same >= k) return mid;
            else if (big >= k) _l = mid + 1;
            else _r = mid - 1;
        }
        return -1;
    };
    for (int i = 0; i < n; i += partSiz)
    {
        auto siz = min(partSiz, n - i);
        auto id = i / partSiz;
        part[id].arr.resize(siz);
        part[id].siz = siz;
        for (int j = 0; j < siz; ++ j)
            part[id].arr[j] = A[i + j],
            part[id].cnt[A[i + j]] ++;
    }
    while (m --)
    {
        int op = scanner.nextInt(),
            l = scanner.nextInt() - 1,
            r = scanner.nextInt() - 1,
            param = scanner.nextInt();
        if (1 == op) update(l, r, param);
        else println(query(l, r, param));
    }
    return 0;
}