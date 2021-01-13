/**
 *
 * 如果两个数字相邻，那么它们乘积也是完全平方数
 * 相邻的两个数字只有两种情况：本身完全平方数/互补缺口
 *
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

template <int n> vector<int> &EulerSieve()
{
    static vector<int> prime;
    bitset<n> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime.push_back(i);
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = true;
            if (i % pp == 0) break;
        }
    }
    return prime;
}

const int N = 3e5 + 5, A = 1e6 + 5;
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
    const auto prime = EulerSieve<A>();
    vector<int> square;
    for (auto p : prime)
    {
        auto pp = (longs)p * p;
        if (pp > A) break;
        else square.push_back(pp);
    }
    unordered_map<int, int> d, m;
    while (T --)
    {
        int n = scanner.nextInt();
        d.clear(), m.clear();
        for (int i = 1; i <= n; ++ i)
        {
            a[i] = scanner.nextInt();
            auto tmp = a[i];
            for (auto pp : square)
            {
                if (pp > tmp) break;
                while (tmp % pp == 0) tmp /= pp;
            }
            ++ d[tmp];
        }
        for (auto [res, cnt] : d)
            m[cnt % 2 ? res : 1] += cnt;
        int dd = 0, mm = 0;
        for (auto [res, cnt] : d) maximize(dd, cnt);
        for (auto [res, cnt] : m) maximize(mm, cnt);
        int q = scanner.nextInt();
        while (q --)
        {
            auto w = scanner.nextLongs();
            println(w ? mm : dd);
        }
    }
    return 0;
}