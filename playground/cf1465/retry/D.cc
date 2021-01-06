/**
 *
 * 没脑子仔细想，觉得瞎几把贪应该就行
 * 看题解，确实是瞎几把贪的样子
 *
 * 但是推导还是有点意思的：
 * - 对于一个子区间 ?..?，将其修改为 1..0 和 0..1 的贡献分别为 (r - l) · x，(r - l) · y
 * - 因此，对于这个区间 ?..?，若将两端修改为不同的数字仅取决于 x 和 y 的相对大小
 * - 换一种说法，对于某个区间 ?..?，总是有一种情况使得 1..0 或者 0..1 更优
 * 总之，可以证明 ? 修改的策略一定是 ..1100.. 或者 ..0011.. 因为：
 * - 假设存在一种情况 ??? -> 101，那么同时存在 1..0 和 0..1
 * - 根据上面的证明，这两中情况中一定是有一种严格优于另一种的
 * - 对于选定区间的其他区间，这样的修改并不会影响到前缀/后缀的 0/1 个数
 * 所以，最终的答案一定是 ..1100.. 或者是 ..0011.. 的形式
 *
 * 真不错，前缀和都能写错，我也是仏了（
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

const int N = 1e5 + 5;
char s[N];
int qm[N], c[2][N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    lll x, y, n;
    scanner(s + 1, x, y);
    n = strlen(s + 1);
    vector<int> qp;
    for (int i = 1; i <= n; ++ i)
    {
        c[0][i] = c[0][i - 1],
        c[1][i] = c[1][i - 1],
        qm[i] = qm[i - 1];
        if (s[i] != '?') ++ c[s[i] - '0'][i];
        else ++ qm[i], qp.push_back(i);
    }
    lll ans = 0, tmp;
    if (x >= y)
    {
        for (int i = 1; i <= n; ++ i)
            if (s[i] == '1')
            {
                ans += (i - c[1][i]) * x;
                ans += (n - i - c[1][n] + c[1][i]) * y;
            }
            else
            {
                ans += c[1][i] * y;
                ans += (c[1][n] - c[1][i]) * x;
            }
        tmp = ans /= 2;
        for (auto q : qp)
        {
            lll pre0 = c[0][q - 1], pre1 = q - pre0 - 1;
            lll suf1 = c[1][n] - c[1][q], suf0 = n - q - suf1;
            tmp = tmp - pre1 * y - suf1 * x + pre0 * x + suf0 * y;
            minimize(ans, tmp);
        }
    }
    else
    {
        for (int i = 1; i <= n; ++ i)
            if (s[i] == '0')
            {
                ans += (i - c[0][i]) * y;
                ans += (n - i - c[0][n] + c[0][i]) * x;
            }
            else
            {
                ans += c[0][i] * x;
                ans += (c[0][n] - c[0][i]) * y;
            }
        tmp = ans /= 2;
        for (auto q : qp)
        {
            lll pre1 = c[1][q - 1], pre0 = q - pre1 - 1;
            lll suf0 = c[0][n] - c[0][q], suf1 = n - q - suf0;
            tmp = tmp - pre0 * x - suf0 * y + pre1 * y + suf1 * x;
            minimize(ans, tmp);
        }
    }
    println(ans);
    return 0;
}