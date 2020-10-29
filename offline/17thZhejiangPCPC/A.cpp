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

int zellerId(int y, int m, int d)
{
    if (m < 3) -- y, m += 12;
    return 365 * y + y / 4 - y /100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307;
}

void zellerParse(int id, int &yy, int &mm, int &dd)
{
    int x = id + 1789995, n, i, j, y, m, d;
    n = 4 * x / 146097, x -= (146097 * n + 3) / 4;
    i = (4000 * (x + 1)) / 1461001, x -= 1461 * i / 4 - 31;
    j = 80 * x / 2447, d = x - 2447 * j / 80, x = j / 11;
    m = j + 2 - 12 * x, y = 100 * (n - 49) + i + x;
    yy = y, mm = m, dd = d;
}

int pre[10010], sum[10010];

int calcUnlimited(int yy)
{
    int ans = 0;
    if (yy / 10 == 202 || yy % 1000 == 202)
        ans += zellerId(yy, 12, 31) - zellerId(yy, 1, 1) + 1;
    else
    {
        if (yy % 10 == 2)
            ans += zellerId(yy, 3, 1) - zellerId(yy, 2, 1);
        else ++ ans;
        ++ ans;
    }
    return ans;    
}

void preProcess()
{
    for (int i = 0; i <= 10000; ++ i)
        pre[i] = calcUnlimited(i);
    sum[0] = pre[0];
    for (int i = 1; i <= 10000; ++ i)
        sum[i] = sum[i - 1] + pre[i];
    return;        
}

int getInternal(int ll, int rr)
{
    if (ll > rr) return 0;
    return max(sum[rr] - sum[ll - 1], 0);
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
    int y1, m1, d1, y2, m2, d2, ss, ee;
    preProcess();
    const auto calcLimited = [&](int yy)
    {
        int ans = 0;
        if (yy / 10 == 202 || yy % 1000 == 202)
            {
                int ts = zellerId(yy, 1, 1), te = zellerId(yy, 12, 31);
                maximize(ts, ss), minimize(te, ee);
                ans += te - ts + 1;
            }
            else
            {
                if (yy % 10 == 2)
                {
                    int ts = zellerId(yy, 2, 1), te = zellerId(yy, 3, 1) - 1;
                    maximize(ts, ss), minimize(te, ee);
                    ans += te - ts + 1;
                }
                else 
                {
                    int tmp = zellerId(yy, 2, 2);
                    if (tmp >= ss && tmp <= ee) ++ ans; 
                }
                int tmp = zellerId(yy, 12, 2);
                if (tmp >= ss && tmp <= ee) ++ ans;
            }
        return ans;    
    };
    while (t --)
    {
        scanner(y1, m1, d1, y2, m2, d2);
        ss = zellerId(y1, m1, d1),
        ee = zellerId(y2, m2, d2);
        // cerr << ee - ss + 1 << endl;
        int ans = getInternal(y1 + 1, y2 - 1);
        ans += calcLimited(y1);
        if (y2 > y1) ans += calcLimited(y2);
        printf("%lld\n", ans);
    }

    return 0;
}

