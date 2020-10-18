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
    int t = scanner.nextInt(), x, y;
    int c1, c2, c3, c4, c5, c6;
    int t1, t2, t3, t4, t5, t6;
    const auto equals = [&]()
    {
        return c1 == t1 && c2 == t2 && c3 == t3
            && c4 == t4 && c5 == t5 && c6 == t6;
    };
    const auto assign = [&]()
    {c1 = t1, c2 = t2, c3 = t3, c4 = t4, c5 = t5, c6 = t6;};
    const auto iterate = [&]()
    {
        do
        {
            t1 = min(c1, c6 + c2);
            t2 = min(c2, c1 + c3);
            t3 = min(c3, c2 + c4);
            t4 = min(c4, c3 + c5);
            t5 = min(c5, c4 + c6);
            t6 = min(c6, c5 + c1);
            assign();
        } while (!equals());
    };
    while (t --)
    {
        scanner(y, x);
        scanner(c1, c2, c3, c4, c5, c6);
        iterate();
        lll ans = 0;
        if (x >= 0 && y >= 0)
        {
            lll step1 = min(x, y);
            lll step6 = y - step1;
            lll step2 = x - step1;
            ans = step1 * c1 + step2 * c2 + step6 * c6;
        }
        else if (x <= 0 && y <= 0)
        {
            x = -x, y = -y;
            lll step4 = min(x, y);
            lll step5 = x - step4;
            lll step3 = y - step4;
            ans = step3 * c3 + step4 * c4 + step5 * c5;
        }
        else
        {
            if (x > 0) ans += (lll)c2 * x;
            else ans += (lll)c5 * -x;
            if (y > 0) ans += (lll)c6 * y;
            else ans += (lll)c3 * -y;
        }
        println(ans);
    }

    return 0;
}

