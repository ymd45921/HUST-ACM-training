/**
 *
 * 意识到 F[n] 只能被拆为 F[n-1] + F[n-2]
 * 因为是树，所以可能会有两个切割位置：
 * - 他们是等价的：F[n-1] + F[n-2] = F[n-2] + F[n-1]
 * - 因为再次拆分之后有：F[n-2] + F[n-3] + F[n-2]
 * - 如果是 Fib 树，怎么切都没事
 * 因此，随便选一个切就对了
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

#define NO println("No"), exit(0)
#define YES println("Yes"), exit(0)

const int N = 2e5 + 5;
bitset<N> fib;

using dist_t = int;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int M = N * 2;

namespace FWS
{
    int head[N];
    int tot;
    edge ee[M * 2];

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

const dist_t inf = 0x3f3f3f3f;

int siz[N];

void count(int u, int fa)
{
    siz[u] = 1;
    FWS::forEach(u, [&](const edge &e)
    {
       if (e.w || e.v == fa) return;
       count(e.v, u), siz[u] += siz[e.v];
    });
}

auto cut_cut(int u, int fa, int x1, int x2)
{
    auto [pu, pv, kd] = make_tuple(0, 0, 0);
    FWS::forEach(u, [&](const edge &e)
    {

    });
    return make_tuple(pu, pv, kd);
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    vector<int> f;
    f.push_back(1);
    fib[1] = true;
    int tmp = 1;
    while (tmp + f.back() < N)
    {
        auto x = tmp + f.back();
        f.push_back(tmp), tmp = x;
        fib[tmp] = true;
    } f.push_back(tmp);
    int n = scanner.nextInt();
    FWS::init(n + 1);
    for (int i = 1; i < n; ++ i)
    {
        int u = scanner.nextInt(),
            v = scanner.nextInt();
        FWS::addEdge(u, v, 0);
        FWS::addEdge(v, u, 0);
    }
    if (!fib[n]) NO;

    return 0;
}