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

void print(__int128 x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) - 48; x /= 10;}
    str[cnt ++] = x - 48;
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

namespace ZellerDateParser
{
    int zellerId(int y, int m, int d)
    {
        if (m < 3) -- y, m += 12;
        return 365 * y + y / 4 - y / 100 + y / 400
               + (153 * (m - 3) + 2) / 5 + d - 307;
    }

    void zellerDate(int id, int &y, int &m, int &d)
    {
        int x = id + 178995, n, i, j;
        n = 4 * x / 146097, x -= (146097 * n + 3) / 4;
        i = (4000 * (x + 1)) / 1461001, x -= 1461 * i / 4 - 31;
        j = 80 * x / 2447, d = x - 2447 * j / 80, x = j / 11;
        m = j + 2 - 12 * x, y = 100 * (n - 49) + i + x;
    }
}

bool isLunar(int y)
{
    if (y % 4) return false;
    else if (y % 100) return true;
    else return !(y % 400);
}

int calcUnlimited(int y)
{
    using namespace ZellerDateParser;
    int ans = 0;
    int first = zellerId(y, 1, 1),
        last = zellerId(y, 12, 31);
    int febSt = zellerId(y, 2, 1),
        febEd = zellerId(y, 3, 1) - 1;
    if (y / 10 == 202 || y % 1000 == 202)
        ans += last - first + 1;
    else
    {
        if (y % 10 == 2) ans += febEd - febSt + 1;
        else ++ ans;
        ++ ans;
    }
    return ans;
}

int calcDirectly(int y)
{
    int ans = 0; bool lunar = isLunar(y);
    if (y / 10 == 202 || y % 1000 == 202)
        ans += lunar ? 366 : 365;
    else
    {
        if (y % 10 == 2) ans += lunar ? 29 : 28;
        else ++ ans;
        ++ ans;
    }
    return ans;
}

int calcLimited(int y, int st, int ed)
{
    using namespace ZellerDateParser;
    if (st > ed) return 0;
    const auto in = [&](int id){return id >= st && id <= ed;};
    int ans = 0;
    int first = max(zellerId(y, 1, 1), st),
        last = min(zellerId(y, 12, 31), ed);
    int febSt = max(zellerId(y, 2, 1), st),
        febEd = min(zellerId(y, 3, 1) - 1, ed);
    if (y / 10 == 202 || y % 1000 == 202)
        ans += max(0, last - first + 1);
    else
    {
        if (y % 10 == 2) ans += max(0, febEd - febSt + 1);
        else if (in(zellerId(y, 2, 2))) ++ ans;
        if (in(zellerId(y, 12, 2))) ++ ans;
    }
    return ans;
}

int sum[10086], whole[10086];
int (*calcMethod)(int) = calcUnlimited;

void preProcess()
{
    const int lim = 10010;
    for (int year = 1; year <= lim; ++ year)
        whole[year] = calcMethod(year);
    sum[0] = 0;
    for (int year = 1; year <= lim; ++ year)
        sum[year] = sum[year - 1] + whole[year];
}

int getInternal(int l, int r)
{
    if (l > r) return 0;
    return sum[r] - sum[l - 1];
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    preProcess();
    using namespace ZellerDateParser;
    while (t --)
    {
        int y1, m1, d1, y2, m2, d2;
        scanner(y1, m1, d1, y2, m2, d2);
        int st = zellerId(y1, m1, d1),
            ed = zellerId(y2, m2, d2);
        int ans = getInternal(y1 + 1, y2 - 1);
        ans += calcLimited(y1, st, ed);
        if (y2 != y1) ans += calcLimited(y2, st, ed);
        println(ans);
    }

    return 0;
}

