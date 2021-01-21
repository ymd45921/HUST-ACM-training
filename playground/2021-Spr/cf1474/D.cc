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
 * 骗来的数据：
 * 5
 * 111111111 333333333 111111111 333333333 222222222
 * 算了，不如重写，，
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
//        if (t > 2863) continue;
//        else if (t == 2863)
//        {
//            println(n);
//            for (int i = 1; i <= n; ++ i)
//                print(a[i], " \n"[i == n]);
//        }
        pre[1] = a[1], suf[n] = a[n];
        pre[0] = 0, suf[n + 1] = 0;
        int legalPre = 1, legalSuf = n;
        for (int i = 2; i <= n; ++ i)
        {
            pre[i] = a[i] - pre[i - 1];
            if (pre[i] < 0) break;
            if (i == n)
                !pre[i] && maximize(legalPre, i);
            else maximize(legalPre, i);
        }
        for (int i = n - 1; i; -- i)
        {
            suf[i] = a[i] - suf[i + 1];
            if (suf[i] < 0) break;
            if (i == 1)
                !suf[i] && minimize(legalSuf, i);
            else minimize(legalSuf, i);
        }
        if (!suf[1]) legalSuf = 1;
        if (legalSuf - legalPre >= 3)
        {puts("NO"); continue;}
        else if (legalPre == n)
        {puts("YES"); continue;}
        bool ok = false;
        for (int j = 3; j <= n + 1; ++ j)
        {
            int tmp[] = {pre[j - 3], a[j - 1], a[j - 2], suf[j]};
            int now = tmp[0], _ok = 1;
            for (int i = 1; i < 4; ++ i)
            {
                now = tmp[i] - now;
                if (now < 0) _ok = 0;
            }
            if (now) _ok = 0;
            if (_ok) {ok = true; break;}
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}