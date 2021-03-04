/**
 *
 * WA：使用 assert 交题查错，发现 x 的计算有问题——我竟然不会写二分
 * WA：浮点还有这种需要注意的地方？这是因为什么啊草（
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

#define PI acosl(-1)
using answer = pair<longs, longs>;

ostream &operator <<(ostream &os, const answer &ans)
{return os << ans.first << " * PI + " << ans.second;}
answer &operator +=(answer &a, const answer &b)
{return a.first += b.first, a.second += b.second, a;}
answer &operator *=(answer &a, const longs t)
{return a.first *= t, a.second *= t, a;}
answer &operator /=(answer &a, const longs t)
{return a.first /= t, a.second /= t, a;}
longd toNumber(const answer &ans)
{return ans.first * PI + ans.second;}

int bruteSolveX(int m)
{
    int ret = 0;
    for (ret = 1; ret <= m; ++ ret)
        if (ret * PI >= m * 2.0) break;
    return ret;
}

int binarySolveX(int m)
{
    int ll = 1, rr = m, x = m;
    while (ll <= rr)
    {
        int mid = (ll + rr) / 2;
        if (mid * PI >= m * 2.0)
            x = mid, rr = mid - 1;
        else ll = mid + 1;
    }
    return x;
}

int floatSolveX(int m)
{return (int)floor(2 * m / PI) + 1;}

auto singleCircle(int m)
{
    longs x = floatSolveX(m);
    assert(x * PI >= m * 2 && (x - 1) * PI < m * 2);
    longs arc = (x - 1) * x / 2 * 2;
    longs str = (m - x) * 2 + 1;
    return [arc, str, m](int r) -> answer
    {
        const int d = r * 2;
        return make_pair(arc * r, str * d * m);
    };
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    const auto cir = singleCircle(m);
    vector<answer> f(n + 1);
    answer ans;
    for (int i = 1; i <= n; ++ i)
        ans += f[i] = cir(i);
    const longs m2 = m * 2;
    for (int R = n; R > 1; -- R)
        for (int r = R - 1; r; -- r)
        {
            auto tmp = f[r];
            tmp *= 2;
            tmp.second += (R - r) * m2 * m2;
            ans += tmp;
        }
    if (m > 1)
    {
        int cnt = (n + 1) * n / 2;
        ans.second += cnt * m2;
    }
    longd out = toNumber(ans);
    out += out * 1e-7;      // ？？？
    cerr << ans << endl;
    cout << fixed << setprecision(10) << out << endl;
    return 0;
}