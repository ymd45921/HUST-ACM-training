/**
 *
 * 引用某位博主的话：
 * - 两个异或：F 要想到二进制拆位，K 要想到满足条件的二元对很有限
 * - 如果上述两个要点都没有想到，那么这场比赛也就倒了==
 * 不得不说还蛮真实的，我就是两个都没有想到，不如说没可能想到吧（
 *
 * HINT: x ^ y >= |x - y| >= gcd(x, y) --> a > b && a | b && a ^ b = (a - b)
 *
 * 为什么套用 STL 还会过不了样例啊== 睡了睡了（
 * 破案了：因为 ^ 的运算符优先级不如 == 高
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

const int N = 1e5 + 5, M = 2e5 + 5;
const int A = 2e5, B = A / 2;
using hash_map = unordered_map<int, int>;

namespace DSU
{
    int fa[N + M], siz[N + M];

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

vector<int> dislike[N + M];
hash_map sets[N + M];
longs ans = 0;
int aa[N + M];

longs count(int index, int x, int cnt)
{
    longs ret = 0;
    for (auto y : dislike[x])
        if (sets[index].count(y))
            ret += 1ll * cnt * sets[index][y];
    return ret;
}

void merge(int x, int y)
{
    using namespace DSU;
    int fx = father(x), fy = father(y);
    if (fx != fy)
    {
        if (siz[fx] < siz[fy]) swap(fx, fy);
        fa[fy] = fx, siz[fx] += siz[fy];
        for (auto &[num, cnt] : sets[fy])
            ans += count(fx, num, cnt);
        for (auto &[num, cnt] : sets[fy])
            sets[fx][num] += cnt;
    }
}

void change(int x, int v)
{
    using namespace DSU;
    int f = father(x);
    if (!-- sets[f][aa[x]]) sets[f].erase(aa[x]);
    ans -= count(f, aa[x], 1);
    ans += count(f, v, 1);
    aa[x] = v, ++ sets[f][v];
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
    DSU::init(n + m);
    for (uint b = 1; b <= B; ++ b)
        for (uint a = b + b; a <= A; a += b)
        {
            auto c = a - b;
            if ((c ^ a) == b)   //// ^ has lower precedence than ==; == will be evaluated first
                dislike[a].push_back(c),
                dislike[c].push_back(a);
        }
    for (int i = 1; i <= n; ++ i)
    {
        aa[i] = scanner.nextInt();
        ++ sets[i][aa[i]];
    }
    while (m --)
    {
        int t = scanner.nextInt();
        if (t == 1)
        {
            int x = scanner.nextInt();
            aa[x] = scanner.nextInt();
            ++ sets[x][aa[x]];
        }
        else if (t == 2)
        {
            int x = scanner.nextInt(),
                y = scanner.nextInt();
            merge(x, y);
        }
        else
        {
            int x = scanner.nextInt(),
                v = scanner.nextInt();
            change(x, v);
        }
        println(ans);
    }
    return 0;
}