/**
 *
 * 傻了，贪心贪不动啊（
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
void println(T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
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

const int N = 1e5 + 5;

lll simulate(lll len, lll tim)
{
    lll aa = len / tim, cb = len % tim;
    lll bb = aa + bool(cb), ca = tim - cb;
    return aa * aa * ca + bb * bb * cb;
}

bool better(lll now, lll then, lll sp)
{
    lll ans1 = simulate(now, sp) + simulate(then, 1);
    lll ans2 = then * then + simulate(now, sp + 1);
    return ans1 < ans2;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    priority_queue<lll> s;
    int n, k, x;
    scanner(n, k);
    for (int i = 1; i <= n; ++ i)
        scanner(x), s.push(x);
    assert(s.size() == n);
    lll t = k - n;
//    while (t --)
//    {
//        auto xx = s.top(); s.pop();
//        auto aa = xx / 2, bb = xx - aa;
//        s.push(aa), s.push(bb);
//    }
    while (t)
    {
        auto xx = s.top(); s.pop();
        auto then = s.top();
        lll aa, bb, ca, cb, sp = 1;
        do
        {
            ++ sp, aa = xx / sp, cb = xx % sp;
            bb = aa + bool(cb), ca = sp - cb;
        } while (better(xx, then, sp) && sp <= t);
        t -= sp - 1;
        while (cb --) s.push(bb);
        while (ca --) s.push(aa);
    }
    assert(s.size() == k);
    lll ans = 0;
    while (!s.empty())
    {
        auto ii = s.top(); s.pop();
        ans += ii * ii;
    } println(ans);

    return 0;
}

