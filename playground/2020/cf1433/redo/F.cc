/**
 *
 * 虽然标答里的 dp[][][][] 很好写
 * 但是我还是觉得我的写法没有问题
 *
 * 唯一的问题应该就是要倒着计算 cnt，否则一个可能选多次
 * 话说这不是背包问题 DP 的常见错误🐎（
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
    void operator()(char &x){x = (char)getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return (char)getchar();}
} scanner;

const int N = 80;
longs f[N][N], F[N][N];
int mat[N][N];

#define now mat[row][col]
#define DEBUG_LOG 0

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, k;
    scanner(n, m, k);
    for (int i = 0; i < n; ++ i)
        for (int j = 0; j < m; ++ j)
            mat[i][j] = scanner.nextInt();
    auto lim = m / 2;
    memset(F, 0xC0, sizeof F);
    const auto _inf = F[0][0];
    for (int row = 0; row < n; ++ row)
    {
        memset(f, 0xC0, sizeof f);
        f[0][0] = 0;
        for (int col = 0; col < m; ++ col)
            for (int cnt = lim - 1; cnt >= 0; -- cnt)
                for (int rem = 0; rem < k; ++ rem)
                    maximize(f[cnt + 1][(rem + now) % k],
                             f[cnt][rem] + now);
        for (int rem = 0; rem < k; ++ rem)
            for (int use = 0; use <= lim; ++ use)
                maximize(F[row][rem], f[use][rem]);
#if DEBUG_LOG
        cerr << "row = " << row << endl;
        for (int cnt = 0; cnt <= lim; ++ cnt)
        {
            for (int rem = 0; rem < k; ++ rem)
                if (f[cnt][rem] < 0) cerr << "- ";
                else cerr << f[cnt][rem] << ' ';
            cerr << endl;
        }
        cerr << endl << "Fill table F[" << row << "]:\n";
        for (int i = 0; i <= lim; ++ i)
            if (F[row][i] < 0) cerr << "- ";
            else cerr << F[row][i] << ' ';
        cerr << endl << endl;
#endif
    }
    memset(f, 0xC0, sizeof f);
    for (int rem = 0; rem < k; ++ rem)
        f[0][rem] = F[0][rem];
    for (int row = 1; row < n; ++ row)
        for (int rem = 0; rem < k; ++ rem)
            for (int use = 0; use < k; ++ use)
                maximize(f[row][(rem + use) % k], f[row - 1][use] + F[row][rem]);
    println(f[n - 1][0]);
#if DEBUG_LOG
    for (int row = 0; row < n; ++ row)
    {
        for (int rem = 0; rem < k; ++ rem)
            if (f[row][rem] < 0) cerr << "- ";
            else cerr << f[row][rem] << ' ';
        cerr << endl;
    }
#endif
    return 0;
}

