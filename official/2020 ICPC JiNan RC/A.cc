/**
 *
 * 罪孽深重的 A 题；虽然说可以想到，但是代码一样不好写
 *
 * 妈的，还真的是线性基板子可以用…… 我真的爬了
 *
 * 首先，两种运算对于矩阵 C 而言都是列独立的，所以分开讨论
 * 详细分析见同目录下的 README.md
 *
 * 某种意义上，线性基也就是高斯消元（）
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
const longs mod = 998244353;

bitset<N> aa[N], bb[N];

template <int N>
class BitsBase
{
    const static auto _siz = N;
    array<bitset<_siz>, _siz> bits;
    using BitsRow = bitset<_siz>;
    int rank = 0;

public:
    BitsBase() = default;

    void clear()
    {
        for (auto &ii : bits) ii.reset();
        rank = 0;
    }

    void insert(BitsRow x)
    {
        int i = _siz;
        while (i --)
            if (!x[i]) continue;
            else if (!bits[i].count())
            {
                bits[i] = x;
                break;
            } else x ^= bits[i];
        if (x.count()) ++ rank;
    }

    int size() {return rank;}
};

longs fastPow(longs a, uint b)
{
    longs ans = 1;
    while (b)
    {
        if (b & 1u) ans = (ans * a) % mod;
        a = (a * a) % mod;
        b >>= 1u;
    }
    return ans % mod;
}

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
        for (int j = 1; j <= n; ++ j)
            aa[i][j] = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            bb[i][j] = scanner.nextInt();
    int cnt = 0;
    BitsBase<N> counter;
    for (int ii = 1; ii <= n; ++ ii)        // 遍历每一个列向量
    {
        counter.clear();
        for (int i = 1; i <= n; ++ i)       // 列向量的每一行
        {
            bitset<N> tmp = aa[i];
            tmp[i] = tmp[i] ^ bb[i][ii];    // 每一项合取式左侧
            counter.insert(tmp);
        }
        cnt += n - counter.size();
    }
    println(fastPow(2, cnt));
    return 0;
}