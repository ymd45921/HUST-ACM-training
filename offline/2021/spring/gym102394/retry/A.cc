/**
 *
 * 这竟然真的是差分约束系统……
 * 但是还可以优化到 O(n(n+m))
 *
 * 我日，我的二分怎么 T 了==
 *
 * SPFA 玄学优化剪枝的解释：
 * - 图的意义：i -> j = k <=> [i, j] <= k
 * - 显然，对于无意义节点 0，到任何位置都应该是非负数
 * - 如果以 0 为起点的 dis < 0，意味着 [0, x] 必须小于负数
 * - 必不可能合理，因此必然出现了负环
 * 也许还有其他优化负环 SPFA 的方法可以卡过这个题目
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

using dist_t = int;
using info_t = pair<dist_t, int>;
using heap_t = priority_queue<info_t, vector<info_t>, greater<>>;
using list_t = vector<int>;

struct edge
{
    int u, v; dist_t w; int next;
    edge() = default;
    edge(int u, int v, dist_t w, int next)
            : u(u), v(v), w(w), next(next) {}
};

const int N = 3060, M = N * 4;

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

dist_t dis[N];
int cnt[N];
bitset<N> inq;

bool spfa(int st, int n)
{
    for (int i = 0; i <= n; ++ i) dis[i] = inf;
    queue<int> hot;
    memset(cnt, 0, sizeof(int) * (n + 1)), inq.reset();
    dis[st] = 0, hot.push(st), cnt[st] = 1;
    inq[st] = true;
    using namespace FWS;
    while (!hot.empty())
    {
        const auto u = hot.front();
        hot.pop();
        inq[u] = false;
        if (dis[u] < 0) return true;    // 玄学，只有起点为 0 时有效
        for (auto c = head[u];
             c != -1;
             c = ee[c].next)
        {
            const edge &e = ee[c];
            const auto v = e.v;
            if (dis[u] + e.w >= dis[v]) continue;
            dis[v] = dis[u] + e.w;
            cnt[v] = cnt[u] + 1;
            if (cnt[v] > n) return true;
            if (inq[v]) continue;
            inq[v] = true, hot.push(v);
        }
    }
    return false;
}

using item = tuple<int, int, int>;

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    vector<item> inst[2];
    for (auto &i : inst) i.reserve(N);
    const auto build =
    [&](int n, dist_t x)
    {
        using namespace FWS;
        init(n + 1);
        for (auto [l, r, k] : inst[0])
            addEdge(r, l - 1, -k);
        for (auto [l, r, k] : inst[1])
            addEdge(l - 1, r, x - k);
        for (int i = 1; i <= n; ++ i)
            addEdge(i - 1, i, 1),
            addEdge(i, i - 1, 0);
        addEdge(n, 0, -x), addEdge(0, n, x);
    };
    while (T --)
    {
        int n, m1, m2, l, r, k;
        $$ n, m1, m2;
        for (auto &i : inst) i.clear();
        while (m1 --)
        {
            $$ l, r, k;
            inst[0].emplace_back(l, r, k);
        }
        while (m2 --)
        {
            $$ l, r, k;
            inst[1].emplace_back(l, r, k);
        }
        int ll = 0, rr = n, ans = n;
        while (ll <= rr)
        {
            int mid = (ll + rr) / 2;
            build(n, mid);
            if (!spfa(0, n + 1)) ans = mid, rr = mid - 1;
            else ll = mid + 1;
        }
        println(ans);
    }
    return 0;
}