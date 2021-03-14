/**
 *
 * 首先，显然的是行列独立：
 * - 我们需要找到行和列的最小循环节
 * - 因此，二维的问题已经转化为了一维
 * 那么如何处理这个一维问题呢？
 * - 一维问题就是个字符串的问题，首先要明确的是找最小循环节
 * - 又因为循环节的长度必然是可以整除原串长度的，所以只需要尝试所有的质因子即可
 *   - 但是这样的话不是有好多个合因子也可以吗？
 *   - 如果两个合因子都是答案，那么它们的最小公约数也是答案
 *   - 修改素数筛，可以构建整数从小到大的质因数分解
 * - 因此，我们可以取每个质因数作为分割次数，在之前分割的基础上分割
 * - 这样，最后不可再分的长度就是最小的循环节的长度，也可以求出段数
 * 然后，我们还需要考虑将一个串分成 x 段，如何判断是循环的
 * - 如果 x 是 2，那么直接判断前判断后半段是否相等即可
 * - 综上所述，我们每次都在以质因子作为段数分解之前分解后的段，因此 x > 2 则是奇数
 *   - 如果允许询问重叠的段，那么假设 x 将现在的段分为了 L 段
 *   - 只需要询问 [1, L - 1] 段和 [2, L] 段是否相等即可，如果相等则必然循环
 *   - 如果不允许询问重叠区间，也可以借助一个中间段完成询问
 *     - 因为已知 x 为基数，设 m = x / 2，则 x = 2 * m + 1
 *     - m + 1 显然 > 1，可以使用上述重叠询问方式进行询问，区间长度为 m
 *     - 选择分出的 m 作为中间段，就可以使用两次询问判断上述 m + 1 的区间
 *     - 因为本质也询问了它们和 m 段的相等情况，所以全段的循环节都可判
 * 综上所述，我们就可以使用少量的询问来完成最小循环节的查找
 * 然后对于最小循环节分成的段数分解因数，统计的个数就是一维的答案
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

const int N = 1005;

int ask(int h, int w, int x1, int y1, int x2, int y2)
{
    cout << "? " << h << ' ' << w << ' ' << x1 << ' '
         << y1 << ' ' << x2 << ' ' << y2 << endl;
    int tmp; cin >> tmp; return tmp;
}

template <int n> auto &sieve()
{
    static vector<int> prime;
    static array<int, n + 1> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i])
            prime.push_back(i), vis[i] = i;
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = pp;
            if (i % pp == 0) break;
        }
    }
    return vis;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    auto p = sieve<N>();
    const auto askM =
    [&](int len, int time) -> bool
    {
        const auto h = n, w = time / 2 * len;
        if (time == 2)
            return ask(h, w, 1, 1, 1, w + 1);
        else return
            ask(h, w, 1, 1, 1, w + 1) &&
            ask(h, w, 1, 1, 1, w + len + 1);
    };
    const auto askN =
    [&](int len, int time) -> bool
    {
        const auto h = time / 2 * len, w = m;
        if (time == 2)
            return ask(h, w, h + 1, 1, 1, 1);
        else return
            ask(h, w, h + 1, 1, 1, 1) &&
            ask(h, w, h + len + 1, 1, 1, 1);
    };
    cin >> n >> m;
    auto [nn, mm] = make_pair(n, m);
    for (int i = nn; i > 1; i /= p[i])
        if (askN(nn / p[i], p[i])) nn /= p[i];
    for (int i = mm; i > 1; i /= p[i])
        if (askM(mm / p[i], p[i])) mm /= p[i];
    const auto nt = n / nn, mt = m / mm;           // 答案不是 nt * mt
    longs np = 0, mp = 0;
    for (int i = 1; i <= nt; ++ i) np += !(nt % i);
    for (int i = 1; i <= mt; ++ i) mp += !(mt % i);
    cout << "! " << np * mp << endl;
    return 0;
}