/**
 *
 * 首先，需要注意一行可以为空，所以循环周期是 k + 1
 * 令人疑惑的是，确定了一个位置之后，将它上下平移后增加的不尽相同
 * 但是，我们几乎可以根据直觉断定对于同构的一组应当增减 k+1
 * 所以，上下移动的增加虽然“有一点规律”，但是是有限的
 * 
 * 还有一个误区就是构造答案上：对于已构造的最小答案，显然，可以再合法的行加上 k+1
 * 只需要保证它比上一行大 1 且比下一行多 k 就显然是合法的，并不需要上下平移和群加
 * 
 * 说到底还是一道思维题，还是比较好做的那种；
 * 至于比赛的时候到底是什么心态导致没有想出来，那我也说不清楚了（
 * 
 * TLE: 暴力尝试加边会超时，需要使用一些方法来加边
 * WA:  您真的会写代码🐎？细节错误给爷整吐了
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

const int N = 1e5 + 5;
longs ans[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    longs n, k, s, a1, low;
    scanner(n, k, s);
    const auto unit = (k + 1) * k / 2;
    for (a1 = 0; a1 <= k; ++ a1)
    {
        longs residue = n - (k + 1 - a1);
        if (residue < 0) low = (a1 + a1 + n - 1) * n / 2;
        else 
        {
            low = residue / (k + 1) * unit;
            residue %= (k + 1);
            low += residue * (residue - 1) / 2;
            low += (k + 1 - a1) * (a1 + k) / 2;
        }
        if (low > s) continue;
        else if (s % (k + 1) == low % (k + 1)) break;
    }
    if (a1 <= k)
    {
        const auto a0 = a1 - 1;
        longs sum = 0;
        for (int i = 1; i <= n; ++ i)
            ans[i] = (a0 + i) % (k + 1),
            sum += ans[i];
        auto t = (s - sum) / (k + 1);
        auto all = (t / n) * (k + 1);
        for (int i = 1; i <= n; ++ i) ans[i] += all;  
        t %= n; assert(t < n);
        for (int i = n - (a0 + n) % (k + 1); t; i -= k + 1)
            for (int j = 0; t && j <= k; ++ j) 
                if (i + j > n || i + j < 1) continue;
                else ans[i + j] += k + 1, -- t;  
        for (int i = 1; i <= n; ++ i)
            print(ans[i], " \n"[i == n]);    
    }
    else println(-1);
    return 0;
}