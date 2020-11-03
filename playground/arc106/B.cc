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

#define lll __int128
#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(args...) cerr << args << endl
#define $$ << ", " <<
#define vars(x, y...) var(x) << ", " << vars(y)
#else
#define eprintf(...)
#define watch(...)
#endif

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) - 48; x /= 10;}
    str[cnt ++] = x - 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

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

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return static_cast<char>(getchar());}
} scanner;

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 2e5 + 5, M = N;
const int INF = 0x3f3f3f3f;

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

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, c, d;
    scanner(n, m);
    vector<int> a(n + 1), b(n + 1);
    FWS::init(n);
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        b[i] = scanner.nextInt();
    while (m --)
    {
        scanner(c, d);
        FWS::addEdge(c, d);
        FWS::addEdge(d, c);
    }
    bitset<N> vis;
    function<pair<int, int>(int, int)> dfs =
    [&](int u, int fa) -> pair<int, int>
    {
        vis[u] = true;
        using namespace FWS;
        int sa = a[u], sb = b[u];
        forEach(u, [&](const edge &e)
        {
            if (vis[e.v] || e.v == fa) return;
            auto [first, second] = dfs(e.v, u);
            sa += first, sb += second;
        });
        return make_pair(sa, sb);
    };
    bool ok = true;
    for (int i = 1; i <= n; ++ i)
        if (!vis[i])
        {
            auto [a, b] = dfs(i, 0);
            if (a == b) continue;
            ok = false; break;
        }
    puts(ok ? "Yes" : "No");
    return 0;
}

