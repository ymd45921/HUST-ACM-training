/**
 *
 * 涉及到位运算，不可不考虑位运算的性质
 * + 连续三个最高位相同，必异或后两个
 * + 数据范围是 Int32，数组是非递减的
 * + 因此，当数组长度大于 32 * 2 时，必定有连续三个最高位一致
 * 那么问题就变成了在数据范围比 32 * 2 小时的答案
 *
 * 因为每次异或合并的数字一定是连续一段才有意义，所以枚举这一段
 * 朴素的情况就是三个数字合并了后两个比第一个小，合并了 3-1-1 次
 * 非朴素情况可能是前后两个数字都需要合并，所以还需要枚举中点
 * 
 * 不要在模板函数中使用返回值类型不确定的表达式！
 * 谁知道会不会把 -1 理解成 4.2e9（）
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
void print(char *s) {printf(s);}
void print(char ch) {putchar(ch);}
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
constexpr auto usz = sizeof(uint) * 8;
uint a[N], b[N], n, sum[100];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    scanner(n);
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    if (n > 64) println(1);
    else
    {
        auto ans = n + 1; sum[0] = 0;
        for (int i = 1; i <= n; ++ i)
            sum[i] = sum[i - 1] ^ a[i];
        for (int l = 1; l <= n; ++ l)
            for (int r = l + 2; r <= n; ++ r)
                for (int m = l; m < r; ++ m)
                {
                    auto ll = sum[m] ^ sum[l - 1];
                    auto rr= sum[r] ^ sum[m];
                    if (ll > rr) minimize(ans, r - l - 1u);
                }
        if (ans > n) println(-1); else println(ans);
    }
    return 0;
}