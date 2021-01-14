/**
 *
 * 这就是 Legendary Grandmaster 级别的贪心题🐎？
 *
 * 解释题意：每次选择一段连续的字串，进行如下的变换
 * - 子串满足 1 的数量和 0 的数量相等
 * - 将子串的每一位都取反
 * - 将子串的顺序翻转为倒序
 * 现在要求求出这个 01 串可以变换达到的字典序最小的串
 *
 * 贪心做法：
 *
 * 发现：如果子串是 10 型或者 01 型，这种变换将毫无意义
 * 启发：将所有的 0 替换为 -1，统计前缀和，并以此建图：
 * - 对于每一个前缀和的值建立节点
 * - 这个节点只会连接到 -1（0）和 +1（1）的节点
 * - 得到的图一定包含一条完整的欧拉路（环），从 0 出发
 * 对于操作，每次操作都是先翻转再倒转：
 * + 限制条件相当于限定了这段区间的路径是一个欧拉环
 * + 翻转相当于将这条欧拉路的一段节点的走向取反
 * + 倒转相当于修改这段区间的前驱后继情况
 * + 总的来看，相当于使得这个欧拉环反向进行
 * 最小的欧拉环是基于两个节点的双向边，一定是先走反向边更优
 * 因此可以建图后贪心，尽可能向更小的节点走，并记录走向
 * 这样得到的记录（走向）组成的串一定是字典序最小的
 *
 * 折线做法（没有看懂）：
 * REFERENCE: https://www.cnblogs.com/2005lz/p/14161455.html
 *
 * 对于 01 串，有一种处理方法是将 0 处理为 -1，1 处理为 +1
 * - 首先，把这样替换的前缀和画成折线图
 * - 那么，一次操作就等价于将一段折线“左右翻转”
 * （没有看懂）
 *
 * 这竟然是 3100 题🐎，真狠啊（
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

const int N = 5e5 + 5;
char s[N];
bitset<N> ans;

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    unordered_map<int, pair<int, int>> graph;
    while (T --)
    {
        scanner(s + 1), graph.clear();
        const int n = strlen(s + 1);
        for (int i = 1, now = 0; i <= n; ++ i)
            if (s[i] - '0') ++ graph[now ++].second;
            else ++ graph[now --].first;
        for (int now = 0, i = 1; i <= n; ++ i)
            if (graph[now].first)
                ans[i] = false, -- graph[now --].first;
            else ans[i] = true, -- graph[now ++].second;
        for (int i = 1; i <= n; ++ i) print((int)ans[i]);
        println();
    }
    return 0;
}