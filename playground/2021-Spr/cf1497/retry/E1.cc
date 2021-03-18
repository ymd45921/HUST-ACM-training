/**
 *
 * 完全平方：两个数字所有质数因子指数互补
 * 因为平方的指数是 2，那么互补的定义就是 mod 2 相等
 *
 * 如果不修改，那么问题退化为划分不包含相同数字的段
 * 这个问题就非常地经典，贪心即可（
 * 最后贪心的部分当然可以 set，也可以向题解那样用 map 维持上次出现的位置
 * 其实像题目标程那样直接用个数组就完了，是最快的；但是空间占用相对较大
 * 但是拿 STL 乱搞也不是不行，就是方便，省一点空间，但花费了一些时间
 *
 * 如何维持这个 pattern？用一个很大的 bitset？
 * 当然是没有必要的：因为 a[i] < 1e7，它所包含的 pattern 乘积不会大于自身
 * 所以只需要存起来：这个时候占用的空间反而更少，更加优雅==
 *
 * PrimeFactorizationSieve() 写成函数有点勉强，，CE 了
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

const int N = 2e5 + 5, A = 1e7 + 7;
int a[N], pattern[N];

// PrimeFactorizationSieve()
namespace PFS
{
    vector<int> prime;
    array<int, A + 1> fact;

    void start()
    {
        for (int i = 2; i <= A; ++ i)
        {
            if (!fact[i])
                prime.push_back(i), fact[i] = i;
            for (auto & pp : prime)
            {
                if ((longs)i * pp > A) break;
                fact[i * pp] = pp;
                if (i % pp == 0) break;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    using PFS::prime, PFS::fact;
    PFS::start();
    while (T --)
    {
        int n = scanner.nextInt(),
            k = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        fill(pattern, pattern + n + 1, 1);
        for (int i = 1; i <= n; ++ i)
        {
            int exp = 0, base = 0, tmp = a[i];
            while (tmp > 1)
            {
                int p = fact[tmp];
                if (base == p) ++ exp;
                else
                {
                    if (exp % 2) pattern[i] *= base;
                    base = p, exp = 1;
                } tmp /= p;
            }
            if (exp % 2) pattern[i] *= base;
        }
        int ans = 1;
        set<int> unique;
        for (int i = 1; i <= n; unique.insert(pattern[i ++]))
            if (unique.count(pattern[i])) ++ ans, unique.clear();
        println(ans);
    }
    return 0;
}