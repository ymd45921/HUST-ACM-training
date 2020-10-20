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

const int N = 250;
char g[N][N];

#define L1 g[0][1]
#define L2 g[1][0]
#define R1 g[n - 1][n - 2]
#define R2 g[n - 2][n - 1]
#define S1 g[0][n - 1]
#define S2 g[n - 1][0]

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
            scanner(g[i]);
        if (L1 == L2 && R1 == R2)
            if (L1 != R1) println(0);
            else
            {
                println(2);
                printf("%d %d\n", 1, 2);
                printf("%d %d\n", 2, 1);
            }
        else if (L1 == L2)
        {
            println(1);
            if (R1 == L1) printf("%d %d\n", n, n - 1);
            else printf("%d %d\n", n - 1, n);
        }
        else if (R1 == R2)
        {
            println(1);
            if (L1 == R1) printf("%d %d\n", 1, 2);
            else printf("%d %d\n", 2, 1);
        }
        else
        {
            println(2);
            if (L1 == R1)
                printf("%d %d\n", 1, 2),
                printf("%d %d\n", n - 1, n);
            else assert(L1 == R2),
                printf("%d %d\n", 1, 2),
                printf("%d %d\n", n, n - 1);
        }
    }


    return 0;
}

