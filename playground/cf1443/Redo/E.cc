/**
 *
 *
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
void print(char *s) {fputs(s, stdout);}
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

const int N = 1e6 + 5, M = 16;
longs a[N], sum[N];

longs prefixSum(int l, int r)
{
    if (l > r) return 0;
    else return sum[r] - sum[l - 1];
}

/**
 *
 * 康托展开： 给定一个 1~N 的排列，求出它的排名（第 x 小）
 * - 公式：rank = 1 + Σ(i:1~n) A[i] * (n - i)!
 * - 公式中 A[i] 代表 Σ(j:i~n) [ a[j] < a[i] ]
 * - 想要知道当前排列的排名，就需要构造出比它小的排列并统计数量
 * - 假设前 x 位完全一致，那么构造的第 x 位一定是小于给定排列
 * - 所以只需要把 x 位和后面小于 a[x] 的数字换到前面就可以了
 * - 使用树状数组优化：维护 A 数组，以优化暴力的遍历计数
 *   + 树状数组的 a 数组用来维护某个数字是否还没有被使用过
 *   + 因为是从前向后遍历，所以树状数组始终维护之后未被使用的数字
 *   + 树状数组的前缀和（c 数组）维护了未使用且小于某数的数量
 * 整体复杂度：O(n · log n) ——线段树/树状数组优化
 *
 * 逆康托展开：类似于进制转换——连续 %(n - 1)!, /(n - 1) 就可以还原 A 数组
 * 因为没想到什么比较合理又美观的实现方法，所以姑且在树状数组上二分，多一个 log
 * 就是用树状数组维护数字的排名，在二分找到指定排名的未标记数字
 */
namespace CantorUnfold
{
    using number = longs;
    constexpr auto N = 20;
    number fact[N], n = N, mod = 998244353;

    template <class T>
    class TreeArrayWithA    // 1-indexed
    {
        vector<T> a, c; int n;
        static inline uint lowBit(uint x) {return x & -x;}

    public:
        explicit TreeArrayWithA(int n): n(n) {a.resize(n + 1), c.resize(n + 1);};
        void add(int i, const T &v){a[i] += v; while (i <= N) { c[i] += v; i += lowBit(i);}}
        template<class arrT> void build(arrT &arr)
        {for (int i = 1; i <= N; ++ i) add(i, a[i] = arr[i]);}
        T ask(int i) {return c[i];}
        T at(int i) {return a[i];}
        T query(int i) {T x = 0; while (i) { x += c[i]; i -= lowBit(i);} return x;}
        T query(int l, int r) {return query(r) - query(l - 1);}
        void clear() {a.resize(n + 1), c.resize(n + 1);}
    };
    TreeArrayWithA<number> ta(N);

    number forRank(int rank)
    {
        int count = n, start = 1;
        while (count > 0)
        {
            auto step = count / 2, it = start + step;
            if (ta.query(it) < rank)
                start = ++ it, count -= step - 1;
            else count = step;
        }
        return start;
    }

    void init(number _n)
    {
        n = _n, fact[0] = 1;
        for (int i = 1; i <= n; ++ i)
            fact[i] = (fact[i - 1] * i) % mod;
    }

    template <class arrT>
    number toRank(arrT &arr)
    {
        number ans = 0; ta.clear();
        for (int i = 1; i <= n; ++ i) ta.add(i, 1);
        for (int i = 1; i <= n; ++ i)
            ans = (ans + (ta.query(arr[i] - 1) * fact[n - i]) % mod) % mod,
            ta.add(arr[i], -1);
        return ans + 1;
    }

    template <class arrT>
    void toArray(number rank, arrT &arr)
    {
        ta.clear(), rank %= fact[n];
        for (int i = 1; i <= n; ++ i) ta.add(i, 1);
        for (int i = n, j = 1; i; -- i, ++ j)
        {
            auto res = rank / fact[i - 1] + 1;
            rank %= fact[i - 1];
            arr[j] = forRank(res);
            ta.add(arr[j], -1);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, q, l, r;
    scanner(n, q);
    int t = n, cnt = min(M, n);
    for (int i = cnt; i; -- i)
        a[i] = t --;
    for (int i = 1; i <= t; ++ i)
        sum[i] = sum[i - 1] + i;
    longs permutation = 0;
    CantorUnfold::init(cnt);
    while (q --)
        if (scanner.nextInt() == 1)
        {
            scanner(l, r);
            int l1 = l, l2 = l, r1 = r, r2 = r;
            minimize(r1, t), maximize(l2, t + 1);
            auto ans = prefixSum(l1, r1);
            if (l2 <= r2) CantorUnfold::toArray(permutation, a);
            for (int i = l2; i <= r2; ++ i) ans += a[i];
            println(ans);
        } else permutation += scanner.nextInt();
    return 0;
}

