/**
 *
 * 看到这个数据范围 5e5，还觉得铁定不是 DP 了
 *
 * 已经注意到了实际上只需要选择一部分数字移动
 * 也意识到了移动数字的顺序无关紧要，只要决定了移动的数字即可
 * 但是还是被周围的数字这种“局部”的环境所限制了思维
 *
 * 考虑保留一部分书籍，移动其他的书本：
 * - 预处理某种颜色 i 的最左和最右以及数量
 * - 令 dp[i] 指后缀 [i, n] 中可以不移动的最大数量
 * - 因为是后缀，所以我们从后向前遍历维护 dp 数组
 *   - i = l[c]，不移动颜色 c，移动 l[c]~r[c] 之间所有其他
 *     - 此时，dp[i] = dp[r[c] + 1] + f[c]
 *   - 否则，可以保持 [i, n] 中所有的颜色 c，移除其他所有
 *     - 此时，dp[i] = cnt[c]，cnt 可以动态的维护
 *     - 注意，此时在 r[c] 右侧的书均被移除，因为 c 并不完整
 *   - 任何情况下，我们都可以移除当前：dp[i] = dp[i + 1]
 * - 这样，就可以在 O(n) 的时间内维护出全数组可保留的最大值
 * 答案是 n - dp[1]；还有一种更加理所应当的 DP 思路：
 * - 依然做预处理左右边界，以及后缀出现最多的颜色
 * - 令 dp[i] 是前缀 [i, n] 可以保留的最多数量
 * - 如果到达了当前颜色的右边界，那么选择保留这种颜色一定是合理的
 *   - 此时考虑还没有遍历的后缀，选择其中最多的颜色保留
 *   - 如果该颜色有出现在前缀中，那么也一定会随着洗牌到达后面
 *   - 所以后缀可以根据预处理选择保留颜色，直接更新答案
 * - 当然，dp[i] = dp[i - 1] 在任何情况都可以进行
 * 这样也可以在维护的过程中得到答案。
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
int a[N], l[N], r[N], cnt[N], f[N], dp[N];

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
    {
        a[i] = scanner.nextInt();
        if (!l[a[i]]) l[a[i]] = i;
        maximize(r[a[i]], i);
        ++ cnt[a[i]];
    }
    for (int i = n; i; -- i)
    {
        dp[i] = dp[i + 1];
        ++ f[a[i]];
        if (i == l[a[i]]) maximize(dp[i], dp[r[a[i]] + 1] + cnt[a[i]]);
        else maximize(dp[i], f[a[i]]);
    }
    println(n - dp[1]);
    return 0;
}