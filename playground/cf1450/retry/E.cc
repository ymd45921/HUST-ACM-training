/**
 *
 * 做题之前先读题：
 * - 一个社会是一个有 n 个点，m 条边的有向图
 * - 每个人是一个节点，一组人际关系是边，每个人有收入 a[i]
 * - 收入不均衡程度用所有人的收入的极差来表示
 * - 对于一组人际关系，如果有 a[j] = a[i] + 1，那么 i 羡慕 j
 * - 如果每一组人际关系都存在上述的羡慕关系，那么是资本主义社会
 * - 对于给定的人际关系，有的已经确定了羡慕的方向，有的没有
 * 题目的条件是上述内容，对于输入的有向图：
 * + 判断它是不是资本主义社会
 * + 如果是资本主义社会，输出可能的一组收入，使得不平等程度最大化
 * 
 * 晚上实在是没啥脑子了，对着标程撸了一发，明天起来看看好了（
 * 不得不说又从标程这里学到了一些良好的代码习惯，这是好事
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

const int N = 205;
const int inf = 0x3f3f3f3f;
int g[N][N];

void floyd(int n)
{
    for (int k = 1; k <= n; ++ k)
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                minimize(g[i][j], g[i][k] + g[k][j]);
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, u, v, b;
    scanner(n, m);
    for (int i = 1; i <= n; ++ i)
        memset(g[i], 0x3f, sizeof(int) * (n + 1)),
        g[i][i] = 0;
    vector<tuple<int, int, int>> edgeList;    
    while (m --)
    {
        scanner(u, v, b);
        g[u][v] = 1;
        g[v][u] = b ? -1 : 1;
        edgeList.emplace_back(u, v, b);
    } floyd(n);
    bool hasNegaCircle = false; 
    pair<int, int> longest(-1, 1);
    for (int i = 1; i <= n; ++ i)
    {
        if (g[i][i] < 0) 
        {hasNegaCircle = true; break;}  // Check negative circle
        for (int j = 1; j <= n; ++ j)
            maximize(longest, {g[i][j], i});
    } 
    bool isBiPartite = true;
    const auto s = longest.second;
    for (auto [u, v, b] : edgeList)
        if (g[s][u] == g[s][v]) 
        {isBiPartite = false; break;}   // Check non-bi-partite
    if (hasNegaCircle || !isBiPartite)
        puts("NO");
    else 
    {
        puts("YES");
        println(longest.first);
        for (int i = 1; i <= n; ++ i)
            print(g[s][i], ' ');
        puts("");    
    }    
    return 0;
}