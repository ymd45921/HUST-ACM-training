/**
 *
 * TODO: Cannot pass the examples
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
    char nextChar() {return static_cast<char>(getchar());}
} scanner;

const int N = 100;
longs a[N][N], f[N][N], F[N][N], G[N][N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, k, l;
    scanner(n, m, k);
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            a[i][j] = scanner.nextInt();
    l = m / 2;
    memset(F, 0, sizeof(F));
    memset(G, 0, sizeof(G));
    for (int i = 1; i <= n; ++ i)
    {
        memset(f, 0, sizeof f);
        for (int j = 1, x = 0; j <= m; ++ j, x = min(j, l))
            for (int select = 0; select < x; ++ select)
                for (int mod = 0; mod < k; ++ mod)
                    if (f[select][mod] % k == mod)
                        maximize(f[select + 1][(mod + a[i][j]) % k],
                                 f[select][mod] + a[i][j]);
        for (int mod = 0; mod < k; ++ mod)
            for (int ll = 0; ll < l; ++ ll)
                if (f[ll][mod] % k == ll)
                    maximize(f[l][mod], f[ll][mod]);
        for (int mod = 0; mod < k; ++ mod)
            if (f[l][mod] % k == mod)
                F[i][mod] = f[l][mod];
    }
    for (int row = 1; row <= n; ++ row)
        for (int i = 0; i < k; ++ i)
            if (G[row - 1][i] % k != i) continue;
            else for (int j = 0; j < k; ++ j)
                if (F[row][j] % k != j) continue;
                else maximize(G[row][(i + j) % k], G[row - 1][i] + F[row][j]);
    println(G[n][0]);
    return 0;
}

