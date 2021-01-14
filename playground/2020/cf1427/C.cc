/**
 *
 * jb 做法，嗯贪心不可取
 *
 * 如果不考虑时间限制，有一个很裸的 DP 做法：
 * - dp[i] 代表第 i 个时间片(ti)前面最多可以遇到的人
 * - 每次更新 i 的时候需要使用 [1...i-1] 的数字更新
 * 当然，这是 n² 的；面对这个题目直接爆炸。
 *
 * 注意到如果这么写的话，r 就完全没有用了。
 * 考虑到两个点的距离不超过 2r，所以 [1...i-1] 中相当前的部分是直接 +1 转移的
 * 如果存在 j in [1...i-1] 有 ti - tj >= 2r 且 ti - tj+1 < 2r，记 j 为分界点
 * 分界点前的节点一定可以无条件 +1 转移，之后的点需要枚举是否可以转移
 * 这样，只需要维护 j 之前的点的最大值，之后枚举后面部分的点并且进行转移即可得到答案
 * 
 * TODO: 没过样例，还有问题
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

const int R = 505, N = 1e5 + 5;
struct people {int x, y, t;} p[N];
int dp[N], inf = 0x3f3f3f3f;

int distance(int i, int j)
{return abs(p[j].x - p[i].x) + abs(p[j].y - p[i].y);}

int period(int i, int j) {return abs(p[j].t - p[i].t);}

bool reachable(int i, int j)
{
    int dt = period(i, j);
    int dx = distance(i, j);
    return dt >= dx;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int r = scanner.nextInt(), rr = r + r,
        n = scanner.nextInt();
    p[0] = {1, 1, 0};
    for (int i = 1; i <= n; ++ i)
        scanner(p[i].t, p[i].x, p[i].y);
    memset(dp, -1, sizeof dp);
    int mx = -1, cur = dp[0] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        while (cur < i && period(cur, i) >= rr)
            maximize(mx, dp[cur ++]);
        for (int j = cur; j < i; ++ j)
            maximize(dp[i], dp[j] + reachable(i, j));
        maximize(dp[i], mx + 1);
    }
    println(dp[n]);
    return 0;
}