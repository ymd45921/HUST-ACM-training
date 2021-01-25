/**
 *
 * 对于一条边 (u, v)：
 * - 若 c[u] != c[v]，答案是显然且不容置疑的
 * - 否则，说明该边在一个环上，DFS 一下就行
 * 然后选择一个合理又美观的写法就好（
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

int c[110];
vector<pair<int, int>> e;
vector<int> to[110];
bitset<11000> dir, done;
bitset<110> vis;

void dfs(int u)
{
    vis[u] = true;
    for (auto i : to[u])
    {
        if (done[i]) continue;
        else done.set(i);
        auto [a, b] = e[i];
        int v = u == a ? b : a;
        dir[i] = v == b;
        if (!vis[v]) dfs(v);
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
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    while (m --)
    {
        int a = scanner.nextInt(),
            b = scanner.nextInt();
        to[a].push_back(e.size()),
        to[b].push_back(e.size());
        e.emplace_back(a, b);
    }
    for (int i = 1; i <= n; ++ i)
        c[i] = scanner.nextInt();
    m = e.size();
    for (int i = 0; i < m; ++ i)
    {
        auto [a, b] = e[i];
        if (c[a] == c[b]) continue;
        else done[i] = true;
        dir[i] = c[a] > c[b];
    }
    for (int i = 0; i < m; ++ i)
    {
        auto [a, b] = e[i];
        if (done[i]) continue;
        assert(!vis[a] && !vis[b]);
        assert(c[a] == c[b]);
        dfs(a);
    }
    for (int i = 0; i < m; ++ i)
        puts(!dir[i] ? "<-" : "->");
    return 0;
}