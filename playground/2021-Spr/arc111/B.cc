/**
 *
 * 很经典的问题：
 * - 相当于每张卡牌是一个边，连接了两个数字的点
 * - 每一条边可以点亮一个端点，问最多有多少端点被点亮
 * - 如果这个图是一颗树，那么最多可以点亮 n - 1
 * - 否则，那么这个图就可以点亮全部的节点
 * 所以，只需判断每一个连通块是不是一棵树即可
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

const int N = 4e5 + 5;
int a[N], b[N];
namespace DSU
{
    int fa[N], siz[N], cnt[N];

    void init(int n)
    {
        for (int i = 0; i <= n; ++ i)
            fa[i] = i, siz[i] = 1, cnt[i] = 0;
    }

    int father(int u)
    {return fa[u] == u ? u : (fa[u] = father(fa[u]));}

    void join(int x, int y)
    {
        int fx = father(x), fy = father(y);
        if (fx == fy) { ++ cnt[fx]; return; }
        if (siz[fx] <= siz[fy]) fa[fx] = fy, siz[fy] += siz[fx], cnt[fy] += cnt[fx] + 1;
        else fa[fy] = fx, siz[fx] += siz[fy], cnt[fx] += cnt[fy] + 1;
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
    int n = scanner.nextInt();
    DSU::init(4e5);
    for (int i = 1; i <= n; ++ i)
        scanner(a[i], b[i]),
        DSU::join(a[i], b[i]);
    longs ans = 0;
    using DSU::siz, DSU::cnt;
    for (int i = 1; i <= 4e5; ++ i)
        if (DSU::father(i) == i)
            ans += min(siz[i], cnt[i]);
    println(ans);
    return 0;
}