/**
 *
 * 甚至看不懂题解……（
 *
 * 小错一手，，但是还是没有想清楚
 * 还有来自网友的申必代码==
 * 有一个和我原代码很像的代码 A 了，可是我看了就关了（
 *
 * 相当于构造一个递增一个递减俩序列加起来等于原序列
 * 贪心： 对于遍历到的位置 i 和它的上一个元素
 * - 如果这个元素更大，那么递增数组一定获得了增量
 * - 如果这个元素更小，那么递减数组一定获得了减量
 * - 始终维护这个增量和减量，如果不合理则退出遍历
 *
 * 还没有搞清楚我自己的代码应该怎么重写 ==
 * 虽然这也是一种很合理常见的思路，但是没搞清还是不行（
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(args...) cerr << args << endl
#define $$ << ", " <<
#define vars(x, y...) var(x) << ", " << vars(y)
#else
#define eprintf(...)
#define watch(...)
#endif

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

const int N = 40000;
int a[N], ll[N], rr[N];

int main()
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
        for (int i = 0; i < n; ++ i)
            a[i] = scanner.nextInt();
        bool ok = true;
        int dec = a[0], inc = 0;
        for (int i = 1; i < n; ++ i)
        {
            assert(dec + inc == a[i - 1]);
            if (a[i] < inc) ok = false;
            (a[i] > a[i - 1] ? inc : dec) += a[i] - a[i - 1];
            if (dec < 0) ok = false;
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}

