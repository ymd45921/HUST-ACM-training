/**
 *
 * 比 k 长的区间真的有必要吗？
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
int a[N];

namespace median
{
    priority_queue<int> small;
    priority_queue<int, vector<int>, greater<>> big;
    int lazy[N];
    int ls = 0, rs = 0;

    const auto pushL = [](int x)
    {small.push(x); ++ ls;};

    const auto pushR = [](int x)
    {big.push(x); ++ rs;};

    const auto popL = []()
    {
        int tmp = small.top();
        while (lazy[tmp])
            -- lazy[tmp], small.pop(),
            tmp = small.top();
        small.pop(), -- ls;
        return tmp;
    };

    const auto popR = []()
    {
        int tmp = big.top();
        while (lazy[tmp])
            -- lazy[tmp], big.pop(),
            tmp = big.top();
        big.pop(), -- rs;
        return tmp;
    };

    int size() {return ls + rs;}

    void maintain()
    {
        while (ls - rs > 1)
            pushR(popL());
        while (rs - ls > 0)
            pushL(popR());
    }

    void push(int x)
    {
        if (small.empty()) pushL(x);
        else
        {
            if (x <= small.top()) pushL(x);
            else pushR(x);
            maintain();
        }
    }

    void pop(int x)
    {
        ++ lazy[x];
        if (x <= small.top()) -- ls;
        else -- rs;
        maintain();
    }

    int get() {return small.top();}
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        k = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    using namespace median;
    int l = 1, r = 0, ans = 0;
    for (r = 1; r <= n; ++ r)
    {
        push(a[r]);
        if (size() >= k)
        {
            maximize(ans, get());
            pop(a[l ++]);
        }
    }
    println(ans);
    return 0;
}