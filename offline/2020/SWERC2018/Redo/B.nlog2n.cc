/**
 *
 * 数据结构做法
 *
 * 比起 O(N) 做法实在太傻逼了，就抄抄代码了==
 *
 * 丑陋的 ST 表
 *
 * 关于 C++ 函数对象，好好学了一课（
 * 不要再乱几把用不熟悉的语法了==
 * 
 * TODO: 为什么常数这么大，我吐了（）
 * 好好找找原因…… 是函数指针的原因还是因为创建对象分配内存？
 * 所以说 class 就图个乐，真要写代码还得 namespace？
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

template <class T>
void println(const T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}

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

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}
} scanner;

const int N = 1e6 + 5;
int a[N], b[N];

class STchart
{
    using cmp_t = const int&(*)(const int&, const int&);
    int table[N + 1][25];
    cmp_t cmp;
    static const int __dep = 21;
public:
    STchart(cmp_t cmp) : cmp(cmp) {}
    template <class arrT>
    void init(const arrT &arr, int n)
    {
        for (int i = 1; i <= n; ++ i)
            table[i][0] = arr[i];
        for (int j = 1; j <= __dep; ++ j)
            for (int i = 1; i + (1 << j) - 1 <= N; ++ i)
                table[i][j] = cmp(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
    }

    int query(int l, int r)
    {
        int k = log2(r - l + 1);
        return cmp(table[l][k], table[r + 1 - (1 << k)][k]);
    }
} st1(max<int>), st2(min<int>);

bool check(int x, int n)
{
    int l = st1.query(n - x + 1, n),
        r = st2.query(n - x + 1, n);
    return r - l + 1 >= x;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        scanner(a[i], b[i]);
    st1.init(a, n), st2.init(b, n);
    int ans = 0;
    for (int i = 1; i <= n; ++ i)
    {
        int ll = 1, rr = i + 1;
        while (ll + 1 < rr)
        {
            auto mid = ll + rr >> 1;
            if (check(mid, i)) ll = mid;
            else rr = mid;
        }
        maximize(ans, ll);
    }
    println(ans);

    return 0;
}