/**
 *
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

const int N = 10086;
const int mod = 1e9 + 7;
int x[N], p[N];
int part[N][1300];

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

longs fastPow(longs a, uint b)
{
    longs ans = 1;
    while (b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    auto prime = EulerSieve<N>();
    unordered_map<int, int> refer;
    for (int i = 0; i < prime.size(); ++ i)
        refer[prime[i]] = i;
    const auto siz = prime.size();
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        x[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        p[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
    {
        int tmp = x[i];
        for (int j = 0; j <= 25; ++ j)
            while (tmp % prime[j] == 0)
                tmp /= prime[j], ++ part[i][j];
        if (tmp > 1) ++ part[i][refer[tmp]];
    }
    auto ans = part[0];
    for (int i = 0; i < siz; ++ i)
        ans[i] = part[1][i] * p[1];
    for (int i = 2; i <= n; ++ i)
        for (int j = 0; j < siz; ++ j)
            minimize(ans[j], part[i][j] * p[i]);
    longs out = 1;
    for (int i = 0; i < siz; ++ i)
        out = (out * fastPow(prime[i], ans[i])) % mod;
    println(out);
    return 0;
}