/**
 *
 * 这个树形…… 还真不算难（
 * 首先要想到市民是尽可能平均分配的，强盗抓大头
 * 如果子树更优，那么一定会更新答案==
 * 
 * 日常爆 int 不用 long long（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
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
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}
} scanner;

const int N = 2e5 + 5, M = N;
int a[N];
longs lvs[N], sum[N];

struct edge
{
    int u, v, w, next;
    edge() = default;
    edge(int u, int v, int w, int next)
            : u(u), v(v), w(w), next(next) {}
};

namespace FWS
{
    int head[N], deg[N];
    int tot;
    edge ee[M * 2];

    void init(int n = N - 1)
    {
        memset(head, -1, sizeof(int) * (n + 1));
        memset(deg, 0, sizeof(int) * (n + 1));
        tot = 0;
    }

    void addEdge(int u, int v, int w = 1)
    {
        ee[tot] = edge(u, v, w, head[u]);
        head[u] = tot ++; ++ deg[u];
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

longs dfsCount(int u)
{
    using namespace FWS;
    if (!deg[u]) return lvs[u] = 1, sum[u] = a[u];
    lvs[u] = 0, sum[u] = a[u];
    longs ans = 0;
    forEach(u, [&](const edge &e)
    {
        auto tmp = dfsCount(e.v);
        lvs[u] += lvs[e.v];
        sum[u] += sum[e.v];
        maximize(ans, tmp);
    });
    return max(ans, sum[u] / lvs[u] + bool(sum[u] % lvs[u]));
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    FWS::init(n);
    for (int v = 2; v <= n; ++ v)
        FWS::addEdge(scanner.nextInt(), v);
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    longs ans = dfsCount(1);;
    println(ans);
    return 0;
}

