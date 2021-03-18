/**
 *
 * 引入了负数真的要麻烦许多啊（（
 *
 * 测试数据：
 * a = [ 0 0 -2 3   ]
 * b = [ 0 -2 -3 -4 ]
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
longs a[N], b[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    longs k;
    scanner(n, m, k);
    vector<longs> ap, an, bp ,bn;
    longs a0 = 0, b0 = 0, pos, neg, zero;
    const auto comparer =
    [](const longs &a, const longs &b)
    {return abs(a) < abs(b);};
    const auto check =
    [&](longs num)
    {
        longs big = 0, same = 0;
        const static auto binaryPositive =
        [&](vector<longs>& aa, vector<longs>& bb)
        {
            for (auto ii : aa)
            {
                auto res = num / ii;
                auto ub = upper_bound(bb.begin(), bb.end(), res, comparer);
                big += bb.end() - ub;
                if (res * ii == num)
                {
                    auto lb = lower_bound(bb.begin(), bb.end(), res, comparer);
                    same += ub - lb;
                }
            }
        };
        const static auto binaryNegative =
        [&](vector<longs>& aa, vector<longs>& bb)
        {
            for (auto ii : aa)
            {
                auto res = (num + sgn(num) * (abs(ii) - 1)) / ii;
                auto lb = lower_bound(bb.begin(), bb.end(), res, comparer);
                big += lb - bb.begin();
                if (res * ii == num)
                {
                    auto ub = upper_bound(bb.begin(), bb.end(), res, comparer);
                    same += ub - lb;
                }
            }
        };
        switch (sgn(num))
        {
            case 0:
                big = pos, same = zero;
                break;
            case 1:
                binaryPositive(ap, bp);
                binaryPositive(an, bn);
                break;
            case -1:
                binaryNegative(ap, bn);
                binaryNegative(an, bp);
                big += pos + zero;
                break;
        }
        return make_pair(big, same);
    };
    for (int i = 1; i <= n; ++ i)
    {
        a[i] = scanner.nextInt();
        switch (sgn(a[i]))
        {
            case 1: ap.push_back(a[i]); break;
            case 0: ++ a0; break;
            case -1: an.push_back(a[i]); break;
        }
    }
    for (int i = 1; i <= m; ++ i)
    {
        b[i] = scanner.nextInt();
        switch (sgn(b[i]))
        {
            case 1: bp.push_back(b[i]); break;
            case 0: ++ b0; break;
            case -1: bn.push_back(b[i]); break;
        }
    }
    pos = ap.size() * bp.size() + an.size() * bn.size();
    neg = ap.size() * bn.size() + an.size() * bp.size();
    zero = a0 * m + b0 * n - a0 * b0;
    sort(ap.begin(), ap.end()), sort(bp.begin(), bp.end());
    sort(an.rbegin(), an.rend()), sort(bn.rbegin(), bn.rend());
    longs rr = 1e12, ll = -1e12;
    longs ans = 0, mid;
    while (ll <= rr)
    {
        mid = (ll + rr) / 2;
        auto [big, same] = check(mid);
        if (same && big < k && big + same >= k)
        { ans = mid; break; }
        else if (big >= k) ll = mid + 1;
        else if (big + same < k) rr = mid - 1;
    }
    println(ans);
    return 0;
}