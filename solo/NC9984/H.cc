/**
 *
 * 大概这就是傻逼吧
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

const int N = 1e5 + 5;
const int mod = 1e9 + 7;
longs inv[N], v[N], ans[N];
using op = pair<char, int>;

stack<op> s;
stack<longs> tmp;
char sign[N];
//vector<int> e[N];
longs now = 0;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N];
    int tot;
    edge ee[N * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++;
    }

    template <class fun>
    void forEach(int u, const fun process)
    {
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
            process(ee[c]);
    }
}

/**
     * 常规的带 mod 的快速幂
     */
longs fastPow(longs a, longs b, longs mod)
{
    longs ans = 1;
    while(b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

/**
 * 注意：此时的 p 必须是质数
 */
longs inverse(longs a, longs p)
{
    if (a > p || a <= 0) return -1;
    else if (a == 1 && p) return 1;
    else return fastPow(a, p - 2, p) % p;
}

void eval(op opt, bool revert)
{
    auto [s, x] = opt;
    if (s == '*' || s == '/')
    {
        auto xx = tmp.top();
        tmp.pop(), now = (now - xx + mod) % mod;
        bool bit = (s == '*') ^ revert;
        xx = xx * (bit ? x : inverse(x, mod)) % mod;
        tmp.push(xx), now = (now + xx) % mod;
    }
    else if (revert) now = (now + mod - tmp.top()) % mod, tmp.pop();
    else tmp.push(s == '+' ? x : mod - x), now = (now + tmp.top()) % mod;
}

void dfs(int u)
{
    s.emplace(sign[u], v[u]);
    eval(s.top(), false);
    ans[u] = now;
    FWS::forEach(u, [](const edge &e){dfs(e.v);});
    eval(s.top(), true), s.pop();
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    FWS::init(n);
    for (int i = 1; i <= n; ++ i)
        v[i] = scanner.nextInt();
    for (int i = 2; i <= n; ++ i)
        FWS::addEdge(scanner.nextInt(), i);
    scanner(sign + 2), sign[1] = '+';
    tmp.push(0), dfs(1);
    for (int i = 1; i <= n; ++ i)
        print(ans[i], " \n"[i == n]);
    return 0;
}