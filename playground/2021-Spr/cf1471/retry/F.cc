/**
 *
 * 这是不是个语文题？
 * 
 * TLE：take a hint，bitset 的很多操作都是暴力（
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

const int N = 3e5 + 5, M = N;

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

namespace DSU
{
    int fa[N], siz[N];

    void init(int n)
    {
        for (int i = 0; i <= n; ++ i)
            fa[i] = i, siz[i] = 1;
    }

    int father(int u)
    {return fa[u] == u ? u : father(fa[u]);}

    void join(int x, int y)
    {
        int fx = father(x), fy = father(y);
        if (fx == fy) return;
        if (siz[fx] <= siz[fy]) fa[fx] = fy, siz[fy] += siz[fx];
        else fa[fy] = fx, siz[fx] += siz[fy];
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
    bitset<N> color, vis;
    queue<int> white;
    vector<int> ans;
    ans.reserve(N);
    while (T --)
    {
        int n = scanner.nextInt(),
            m = scanner.nextInt();
        FWS::init(n), DSU::init(n);
        while (m --)
        {
            int u = scanner.nextInt(),
                v = scanner.nextInt();
            FWS::addEdge(u, v), FWS::addEdge(v, u);
            DSU::join(u, v);
        }
        if (DSU::siz[DSU::father(1)] < n)
        {puts("NO"); continue;}
        while (!white.empty()) white.pop();
        for (int i = 1; i <= n; ++ i)
            vis[i] = color[i] = false;
        vis[1] = color[1] = true;
        ans.clear(), ans.push_back(1);
        FWS::forEach(1, [&](const edge &e)
        {vis[e.v] = true; white.push(e.v);});
        while (!white.empty())
        {
            int u = white.front(); white.pop();
            FWS::forEach(u, [&](const edge &e)
            {
                int v = e.v;
                if (vis[v]) return;
                vis[v] = color[v] = true;
                ans.push_back(v);
                FWS::forEach(v, [&](const edge &e)
                {if (!vis[e.v]) white.push(e.v), vis[e.v] = true;});
            });
        }
        puts("YES");
        println(ans.size());
        for (auto ii : ans) print(ii, ' ');
        println();
    }
    return 0;
}