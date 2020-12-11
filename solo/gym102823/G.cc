/**
 *
 * 这依然是一道思路正确但是没能一遍过的题目
 * ……好吧 其实思路也未必正确==
 * 因为只要求 gcd 不为 1，所以我们求出的 gcd 未必是最后的 gcd
 * 有任何一个最小的 gcd 因子作为 gcd 就可以满足题意
 * 
 * 当然，你也要注意到因子不是质因子，求法没有那么麻烦 ==
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
int a[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    for (int t = 1; t <= T; ++ t)
    {
        int n = scanner.nextInt();
        int $gcd = 0, ans = 0, low = 1e9 + 7;
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt(),
            minimize(low, a[i]);
        for (int i = 1; i < n; ++ i)
            $gcd = gcd($gcd, a[i + 1] - a[i]);
        if (n == 1) $gcd = 0;    
        if (!$gcd) ans = max(0, 2 - a[1]);
        else if ($gcd == 1) ans = -1;
        else if (low % $gcd) 
        {
            vector<int> factor;
            longs tmp = $gcd;
            for (longs i = 2; i * i <= tmp; ++ i)
                if (tmp % i == 0)
                    factor.push_back(i),
                    factor.push_back(tmp / i);  
            factor.push_back($gcd);  
            ans = INT32_MAX;            
            for (auto can : factor)
                if (low % can) minimize(ans, can - low % can);
                else minimize(ans, 0);
        }
        else ans = 0;
        printf("Case %d: ", t);
        println(ans);
    }
    return 0;
}