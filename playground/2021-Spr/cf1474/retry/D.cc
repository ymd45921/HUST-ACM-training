/**
 *
 * 首先，应该意识到 check 是线性的：
 * - 两端只有一种方法
 * - 如果消去了两端，会产生新的两端
 * - 递归直到销完
 * 比起怎么启发式消除，更应该规范化的处理问题
 *
 * 此外，交换两个相邻的堆，只会影响最多四堆
 * 因为上面的 check 方法已经揭示了这是个线性的过程
 *
 * 需要注意，线性判断的最后，需要堆为空才成功
 * 
 * 妈耶，骗了一堆数据，，我是傻逼
 * 你那么急干嘛呢==
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

const int N = 2e5 + 5;
int a[N], pre[N], suf[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    while (t --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        pre[0] = suf[n + 1] = 0;
        int legalPre = 0, legalSuf = n + 1;
        for (int i = 1; i <= n; ++ i)
        {
            pre[i] = a[i] - pre[i - 1];
            if (pre[i] < 0) break;
            if (i != n || !pre[i])
                maximize(legalPre, i);
        }
        if (legalPre == n) {puts("YES"); continue;}
        for (int i = n; i >= 1; -- i)
        {
            suf[i] = a[i] - suf[i + 1];
            if (suf[i] < 0) break;
            if (i != 1 || !suf[i])
                minimize(legalSuf, i);
        }
        const int lim = min(n - 2, legalPre),
            st = max(legalSuf - 3, 0);
        bool ok = false;
        for (int i = st; i <= lim; ++ i)
        {
            int tmp[] = {pre[i], a[i + 2], a[i + 1], suf[i + 3]};
            int now = 0; bool _ok = true;
            for (int ii : tmp)
            {
                now = ii - now;
                if (now < 0) _ok = false;
            }
            if (now) _ok = false;
            ok |= _ok; if (ok) break;
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}