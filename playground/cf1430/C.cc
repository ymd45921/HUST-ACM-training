/**
 *
 * 应该这样就可以吧，虽然不会证明
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) ^ 48; x /= 10;}
    str[cnt ++] = x ^ 48;
    while (cnt --) putchar(str[cnt]);
}
template <class T>
void println(T x) {puts(to_string(x).c_str());}
void println(const char *s) {puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}
void println(const lll x)
{lll xx = x; print(xx), putchar('\n');}

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
const int N = 2e5 + 5;
int a[N];
bitset<N> flag;

void init(int n)
{for (int i = 1; i <= n; ++ i) a[i] = i;}

int calc(int aa, int bb)
{return aa + bb - (aa + bb) / 2;}

void preProcess()
{
    a[0] = 0, a[1] = 1, a[2] = 2;
    for (int i = 3; i < N; ++ i)
        a[i] = min(calc(a[i - 1], i), calc(a[i - 1] + 1, 1)),
        flag[i] = (calc(a[i - 1], i) < calc(a[i - 1] + 1, 1));
    flag[2] = true;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t, n;
    scanner(t);
    preProcess();
    while (t --)
    {
        scanner(n);
        stack<pair<int, int>> ans;
        int addon = 0;
        for (int i = n; i > 1; -- i)
            if (flag[i]) ans.push({a[i - 1] + addon, i + addon});
            else ++ addon, ans.push({a[i - 1] + addon, addon});
        println(a[n]);
        while (!ans.empty())
        {
            auto ii = ans.top();
            ans.pop();
            printf("%d %d\n", ii.first, ii.second);
        }
    }

    return 0;
}

