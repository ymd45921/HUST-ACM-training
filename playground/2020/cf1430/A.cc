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
    while (t --)
    {
        scanner(n);
        auto xx = n % 7;
        int a = 0, b = 0, c = n / 7;
        switch (xx)
        {
            case 0: break;
            case 1: a = 1, b = 1, -- c; break;
            case 2: a = 3, b = 0, -- c; break;
            case 3: a = 1;  break;
            case 4: a = 2, b = 1, -- c; break;
            case 5: b = 1; break;
            case 6: a = 2; break;
            default: c = -1;
        }
        if (c < 0) puts("-1");
        else printf("%d %d %d\n", a, b, c);
    }

    return 0;
}

