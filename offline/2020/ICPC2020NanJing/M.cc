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

const int N = 2e3 + 5;
const longs inf = 1e9 + 7;
int p[N], hp[N], siz[N];
longs f[N][N][2];       // f[u][hasKilled][isAlive]
vector<int> suc[N];

void dfs(int u)
{
    siz[u] = 1;
    f[u][1][0] = 0, f[u][0][1] = hp[u];
    for (const auto &v : suc[u])
    {
        dfs(v); int Siz = siz[u] + siz[v];
        for (int allKill = Siz; allKill >= 0; -- allKill)
        {
            int lb = max(0, allKill - siz[u]),
                rb = min(allKill, siz[v]);
            for (int subKill = lb; subKill <= rb; ++ subKill)
            {                   // 对于一个节点，最多杀完全部子树：O(n²)
                int nowKill = allKill - subKill,
                    alive = siz[u] - nowKill;
                if (alive)      // 本层及子树至少包含一个存活节点
                    minimize(f[u][allKill][1], f[u][nowKill][1] + 
                        min(f[v][subKill][1] + hp[v], f[v][subKill][0]));
                if (nowKill)    // 至少有一个节点是在非子树中删除的
                    minimize(f[u][allKill][0], f[u][nowKill][0] + 
                        min(f[v][subKill][0], f[v][subKill][1]));
            }    
        }
        siz[u] += siz[v];
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
    while (T --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            suc[i].clear();
        for (int i = 2; i <= n; ++ i)
            p[i] = scanner.nextInt(),
            suc[p[i]].push_back(i);
        for (int i = 1; i <= n; ++ i)
            hp[i] = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            memset(f[i], 0x3f, sizeof f[0]);    
        dfs(1);
        for (int m = 0; m <= n; ++ m)
            print(min(f[1][m][0], f[1][m][1]), " \n"[m == n]);
    }

    return 0;
}