/**
 *
 * 是一个细节很多的题目，虽然不难做，但是要大脑清醒才行
 *
 * 首先，这颗题目可以从无限大情况入手，考虑推柿子
 * - a > cb：可以打出无限大伤害，每次打击都是有净伤害的
 * - a <= cb：伤害上界总是存在，可以这样推算：
 *   + 由题意，一个技能发动期间，可以再发起 x = c / d 次技能
 *   + 第一个技能结束后再发起的每一个技能都是等价的，伴随着一个技能的结束
 *   + 因为每个技能的结束都是伴随着副作用，所以每次发起技能只会起反作用
 *   + 在 Excel 以时间为轴画图可知，之后每次发动技能都会带来 cb - a 的反作用
 *   + 考虑到反作用，当发动技能时反作用小时才能带来收益
 * - 综上所述，上界总是发动技能且带来收益的最后一个技能时的伤害
 *
 * 做出来了！但是如果硬模拟无疑会被数据干翻，得想点办法优化
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
    static bool isSeparator(int x)
    {return x == ' ' || x == '\n';}

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
    char nextChar()
    {int x = getchar(); while (isSeparator(x)) x = getchar(); return x;}
} scanner;

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
        lll a, b, c, d;
        scanner(a, b, c, d);
        if (c * b < a) println(-1);
        else
        {
#ifdef BRUTE
            lll ans = a, time = 0, on = 1;
            lll tmp = a;
            while (time <= c)
            {
                time += d;
                tmp = tmp + a - on * d * b;
                maximize(ans, tmp);
                ++ on;
            }
            println(ans);
#else
            lll db = d * b, k = a / db;
            lll ans = (k + 1) * a - k * (k + 1) / 2 * db;
            println(ans);
#endif
        }
    }

    return 0;
}

