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

const int N = 1050;
int mat[N][N];

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
        int n, m, a, b;
        scanner(n, m, a, b);
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                mat[i][j] = scanner.nextInt();
        int I = n - a + 1, J = m - b + 1; 
        bool ok = true;       
        for (int i = 1; ok && i <= I; ++ i)
            for (int j = 1; ok && j <= J; ++ j)
            {
                int todo = mat[i][j];
                if (!todo) continue;
                for (int x = 0; ok && x < a; ++ x)
                    for (int y = 0; ok && y < b; ++ y)
                        if (mat[i + x][j + y] < todo) ok = false;
                        else mat[i + x][j + y] -= todo;
            }  
#if 0
        cerr << var(I) << ", " << var(J) << endl;
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= m; ++ j)
                cerr << mat[i][j] << ' ';
            cerr << endl;    
        }
#endif
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= m; ++ j)
                if (mat[i][j]) ok = false;   
        puts(ok ? "^_^" : "QAQ");           
    }


    return 0;
}

