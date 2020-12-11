/**
 *
 * 不管怎么说，边界值是可以为 0 的
 * 所以得到的 b 数列未必是每一位都差 1 的
 * 
 * 以后遇到需要生成这种数组就这么写了（
 * 虽然算不上是多少优雅的写法，但是总比过不了好 ==
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
int a[N], b[N];

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
        longs sumA = 0, sumB = 0, delta;
        for (int i = 1; i <= n; ++ i)
            sumA += a[i] = scanner.nextInt();
        memset(b, 0, sizeof(int) * (n + 1));    
        b[0] = b[n + 1] = a[0] = a[n + 1] = -1;
        vector<int> minimum;
        for (int i = 1; i <= n; ++ i)
            if (a[i] < a[i - 1] && a[i] < a[i + 1])
                minimum.push_back(i);
        for (int i = 1; i <= n; ++ i)
            if (a[i] < a[i - 1]) break;
            else maximize(b[i], b[i - 1] + 1);
        for (int i = n; i >= 1; -- i)
            if (a[i] < a[i + 1]) break;
            else maximize(b[i], b[i + 1] + 1);
        for (auto pos : minimum)
        {
            b[pos] = 0;
            for (int i = pos + 1; i <= n; ++ i)
                if (a[i] < a[i - 1]) break;
                else maximize(b[i], b[i - 1] + 1);
            for (int i = pos - 1; i >= 1; -- i) 
                if (a[i] < a[i + 1]) break;
                else maximize(b[i], b[i + 1] + 1);        
        }  
        for (int i = 1; i <= n; ++ i) sumB += b[i];
        delta = sumA - sumB;           
        printf("Case %d: ", t);
        println(delta % 2 ? "Alice" : "Bob");    
    }
    return 0;
}