/**
 *
 * 其实不难，但是要想清楚，而且代码要稳一点：
 * - 首先注意到：负轴和正轴是两个独立的问题，我们只考虑正轴
 * - 然后注意到：将一排盒子的最左侧位置推到一个终点一定是最优的
 *   - 如果最左侧的盒子不在终点，假设它距离最近的终点距离为 x
 *   - 如果最右侧向前 x 步内有终点，那么一定是向右推更优的
 *   - 如果没有，那么向右边推 x 步对于当前的答案也没有任何影响
 * - 这样，我们就可以遍历每个终点作为当前推着的一排箱子的左侧
 * - 然后，使用双指针维护要将第一个箱子推到这里维护的箱子数量
 * - 接着，双指针维护这一排箱子右侧无法到达的第一个终点的位置
 *   - 这样，这一排箱子内部有的终点数量就已经维护得到了
 *   - 同时，维护箱子数量的时候也可以得到第一个外面的箱子位置
 *   - 这样，就可以用这个位置预处理的后缀原位数得到答案
 * - 找到最大答案，并且和另一侧的答案求和即可，复杂度是线性的
 * 
 * 当然，这个题似乎还是可以二分或者用 STL 嗯混的，思路大致同上
 * 当然复杂度就会多一个额外的 log，没有双指针优雅。
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

const int N = 2e5 + 5;
int a[N], b[N], su[N];

int solveHalf(vector<int> &aa, vector<int> &bb)
{
    const int n = aa.size(), m = bb.size();
    su[n] = su[m] = 0;
    for (int i = n - 1, j = m - 1; i >= 0; -- i)
    {
        su[i] = su[i + 1];
        while (j >= 0 && bb[j] > aa[i]) -- j;
        if (j >= 0 && bb[j] == aa[i]) ++ su[i];
    }
    int ans = 0, cnt = 0, rr = 0;
    for (int ll = 0; ll < m; ++ ll)
    {
        while (cnt < n && aa[cnt] <= bb[ll] + cnt) ++ cnt;
        while (rr < m && bb[rr] - bb[ll] < cnt) ++ rr;
        maximize(ans, rr - ll + su[cnt]);
    }
    return ans;
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
        int n = scanner.nextInt(),
            m = scanner.nextInt();
        vector<int> al, ar, bl, br;
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt(),
            (a[i] < 0 ? al : ar).push_back(abs(a[i]));
        for (int i = 1; i <= m; ++ i)
            b[i] = scanner.nextInt(),
            (b[i] < 0 ? bl : br).push_back(abs(b[i]));
        reverse(al.begin(), al.end());
        reverse(bl.begin(), bl.end());
        println(solveHalf(al, bl) + solveHalf(ar, br));
    }
    return 0;
}