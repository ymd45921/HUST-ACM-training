/**
 *
 * 这就是骗保人🐎
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
ulongs mask[32], num[32];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int q = scanner.nextInt();
    uint u, v;
    for (uint i = 0; i < 32; ++ i)
        mask[i] = 1u << i;
    while (q --)
    {
        scanner(u, v);
        bool ok = u <= v;
        if (ok && u != v)
        {
            int pu = __builtin_popcount(u),
                pv = __builtin_popcount(v);
            ok &= pv <= pu;
            bitset<32> bs = u;
            fill(num, num + 32, mask[31]);
            minimize(num[pu], (ulongs)u);
            uint high = 0;
            vector<int> bit;
            for (uint i = 0; i < 32; ++ i)
                if (bs[i]) maximize(high, i), bit.push_back(i);
            minimize(num[1], mask[high + 1]);
            for (uint i = 1; i < pu; ++ i)
            {
                auto pos = pu - i;
                for (uint j = i; j < pu; ++ j)
                    if (!bs[bit[j] + 1])
                    {
                        ulongs tmp = mask[mask[bit[j] + 1]];
                        for (uint k = j + 1; k < pu; ++ k)
                            tmp += mask[bit[k]];
                        minimize(num[pos], tmp);
                    }
            }
            auto uu = __builtin_ffs(num[pu]);
            auto vv = __builtin_ffs(v);
            ok &= uu <= vv;
        }
        output: puts(ok ? "YES" : "NO");
    }
    return 0;
}