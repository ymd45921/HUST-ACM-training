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
    if (tim <= 1) return len * len;
    lll aa = len / tim, cb = len % tim;
    lll bb = aa + bool(cb), ca = tim - cb;
    return aa * aa * ca + bb * bb * cb;
}

lll contrib(lll len, lll tim)
{return simulate(len, tim) - simulate(len, tim + 1);}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    using item = pair<lll, pair<lll, int>>;
    priority_queue<item> heap;
    vector<lll> a;
    int n, k, x;
    scanner(n, k);
    for (int i = 1; i <= n; ++ i)
        scanner(x), a.push_back(x);
    lll t = k - n;
    for (lll ii : a)
    {
        lll dx = contrib(ii, 1);
        heap.push({dx, {ii, 1}});
    }
    while (t --)
    {
        auto ii = heap.top(); heap.pop();
        lll dx = contrib(ii.second.first, ii.second.second + 1);
        heap.push({dx, {ii.second.first, ii.second.second + 1}});
    }
    lll ans = 0;
    while (!heap.empty())
    {
        auto ii = heap.top(); heap.pop();
        ans += simulate(ii.second.first, ii.second.second);
    } println(ans);

    return 0;
}

