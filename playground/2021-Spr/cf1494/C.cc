/**
 *
 * 不对，，维护 mx 可能没什么意义
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
int a[N], b[N], aa[N], bb[N];
int mx[N], po[N], sta[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    set<int> pos;
    while (T --)
    {
        int n = scanner.nextInt(),
            m = scanner.nextInt();
        int start = 0; pos.clear();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt(),
            pos.insert(a[i]);
        for (int i = 1; i <= m; ++ i)
            b[i] = scanner.nextInt(),
            start += pos.count(b[i]);
        int ars, als, brs, bls;
        for (int i = 1; i < n; ++ i)
            if (a[i] < 0 && a[i + 1] > 0)
                ars = i + 1, als = i;
        for (int i = 1; i < m; ++ i)
            if (b[i] < 0 && b[i + 1] > 0)
                brs = i + 1, bls = i;
        for (int i = brs; i <= m; ++ i)
            if (b[i - 1] + 1 == b[i])
                bb[i] = bb[i - 1] + 1;
            else bb[i] = 1;
        for (int i = bls; i > 0; -- i)
            if (b[i] + 1 == b[i + 1])
                bb[i] = bb[i + 1] + 1;
            else bb[i] = 1;
        for (int i = 1; i <= bls; ++ i)
            if (mx[i] <= bb[i])
                mx[i] = bb[i], po[i] = i;
            else po[i] = po[i - 1];
        for (int i = m; i >= brs; -- i)
            if (mx[i] <= bb[i])
                mx[i] = bb[i], po[i] = i;
            else po[i] = po[i + 1];
        for (int i = brs, j = ars; i <= m; ++ i)
        {
            sta[i] = i == brs ? 0 : sta[i - 1];
            while (a[j] < b[i] && j <= n) ++ j;
            if (j <= n && a[j] == b[i]) ++ sta[i];
        }
        for (int i = bls, j = als; i > 0; -- i)
        {
            sta[i] = i == bls ? 0 : sta[i + 1];
            while (a[j] > b[i] && j > 0) -- j;
            if (j > 0 && a[j] == b[i]) ++ sta[i];
        }
        int ls = sta[1], rs = sta[m], ll = ls, rr = rs;
        for (int i = ars, j = brs; i <= n; ++ i)
        {
            int acc = i - ars + 1, ind = a[i];
            while (j <= m && b[j] < ind) ++ j;
            if (j <= m) maximize(rr, min(acc, mx[j]) + rs - sta[j]);
        }
        for (int i = als, j = bls; i > 0; -- i)
        {
            int acc = als - i + 1, ind = a[i];
            while (j > 0 && b[j] > ind) -- j;
            if (j > 0) maximize(ll, min(acc, mx[j]) + ls - sta[j]);
        }
        assert(ls + rs == start);
        println(max(ll + rr, start));
    }
    return 0;
}