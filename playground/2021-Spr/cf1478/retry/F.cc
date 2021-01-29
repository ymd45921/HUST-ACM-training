/**
 *
 * 优美的中国话：5000? 5000!!
 *
 * 因为数据范围非常的和善，导致了无论多么乱来的方法都能够被接受
 * 比如：
 * - 寻找最远点：每次遍历寻找最远的点，可以反证法证明其正确性
 * - 插入排序：（没有看懂）
 * - DFS（不是）：虽然说是 O(5000!) 的，但是很快就能找到而中断
 * 等等，，怎么出题人自己也没有证明方法二）
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

const int N = 5050;
struct {int x, y;} g[N];

longs dot(longs x1, longs y1, longs x2, longs y2)
{return x1 * x2 + y1 * y2;}

longs distance(longs x1, longs y1, longs x2, longs y2)
{return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);}

void answer(int n)
{
    vector<int> p;
    for (int i = 1; i <= n; ++ i)
    {
        p.emplace_back(i);
        for (int j = i - 1; j >= 2; -- j)
        {
            auto &a = g[p[j]],
                &b = g[p[j - 1]],
                &c = g[p[j - 2]];
            longs x1 = a.x - b.x, y1 = a.y - b.y;
            longs x2 = b.x - c.x, y2 = b.y - c.y;
            if (dot(x1, y1, x2, y2) >= 0)
                swap(p[j], p[j - 1]);
            else break;
        }
    }
    for (auto i : p) print(i, ' ');
}

void normal(int n)
{
    bitset<N> vis;
    vector<int> ans;
    vis[1] = true, ans.push_back(1);
    while (ans.size() < n)
    {
        int i = ans.back();
        pair<longs, int> select;
        for (int j = 1; j <= n; ++ j)
            if (!vis[j])
                maximize(select, {distance(g[i].x, g[i].y, g[j].x, g[j].y), j});
        if (select.second)
            vis[select.second] = true,
            ans.push_back(select.second);
    }
    for (auto i : ans) print(i, ' ');
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
    for (int i = 1; i <= n; ++ i)
        scanner(g[i].x, g[i].y);
    normal(n);
    return 0;
}