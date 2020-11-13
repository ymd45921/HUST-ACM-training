/**
 *
 * 做法很取巧，因为虽然需要重排列 1e10 次，但是涉及到的更改不会超过 15 个数字
 * 所以只需要预处理这些部分的数字的排列，然后 O(n) 应用就可以修改
 * 前面的部分可以使用前缀和优化，后面的十几个数字循环求和即可求出区间和
 * 
 * 但是实现起来意外地还有不少问题（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define lll __int128
#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
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

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

const int N = 2e5 + 5;
int a[N], sum[N];
int pre[N][21], now[21], tmp[21];

auto initReplace(int n)
{
    const auto lim = min(n, 16);
    for (int i = 1; i <= lim; ++ i)
        pre[0][i] = now[i] = i;
    const auto siz = sizeof(int) * (lim + 1);
    for (int x = 1; x < N; ++ x)
    {
        memcpy(pre[x], pre[x - 1], siz);
        next_permutation(pre[x] + 1, pre[x] + 1 + lim);
    }
    const auto full = sizeof(int) * (lim + 1);
    return [lim, full](int t)
    {
        for (int i = 1; i <= lim; ++ i)
            tmp[i] = now[pre[t][i]];
        memcpy(now, tmp, full);
    };
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(), q = scanner.nextInt();
    sum[0] = 0;
    for (int i = 1; i <= n; ++ i)
        sum[i] = sum[i - 1] + (a[i] = i);
    const auto start = max(1, n - 15), dx = start - 1;
    const auto apply = initReplace(n);
    while (q --)
        if (scanner.nextInt() == 1)
        {
            int l, r; scanner(l, r);
            int l1 = l, l2 = max(start, l),
                r1 = min(r, start - 1), r2 = r;
            int ans = r1 < l1 ? 0 : sum[r1] - sum[l1 - 1];
            for (int ii = l2; ii <= r2; ++ ii)
                ans += now[ii - dx] + dx;
            println(ans);
        } else apply(scanner.nextInt());
    return 0;
}


