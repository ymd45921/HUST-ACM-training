/**
 *
 * 我日，我不是很会写了
 * 
 * 这是我自己想出来的，不是别人教的！！
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;
using lll = __int128;

#define minimize(a, b...) ((a) = min({(a), b}))
#define maximize(a, b...) ((a) = max({(a), b}))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#endif

template <class printable>
void trace(const char *name, printable &&value)
{cerr << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    cerr.write(names, separate - names) << " = " << value << ',';
    trace(separate + 1, list...);
}

template <class T>
void print(T x)
{
    if (x < 0) { putchar('-'); x = -x; }
    static char str[40]; int cnt = 0;
    while (x > 9) { str[cnt ++] = (x % 10) + 48; x /= 10;}
    str[cnt ++] = x + 48;
    while (cnt --) putchar(str[cnt]);
}
void print(string &s) {printf(s.c_str());}
void print(const char *s) {printf(s);}
void print(char *s) {printf(s);}
void print(char ch) {putchar(ch);}
template <class T, class ...Ts>
void print(T x, Ts ...xs) {print(x), print(xs...);}
void println() {puts("");}
template <class T>
void println(T x)
{print(x), putchar('\n');}

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

    static inline bool isBlank(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}
    template <class T, class... Ts>
    void operator()(T &&x, Ts &&... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;

const int N = 1060, M = 1e6 + 5;
int a[N * 2];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    map<int, int> cnt;
    queue<pair<int, int>> ans;
    const auto recount = [&](int nn)
    {
        cnt.clear();
        for (int i = 1; i <= nn; ++ i)
            ++ cnt[a[i]];
    };
    const auto tryTo = [&](int nn, int mate, int n)
    {
        recount(nn);
        auto rend = cnt.rend();
        int now = a[nn]; -- cnt[a[nn]];
        bool ok = true;
        -- cnt[mate];
        while (!ans.empty()) ans.pop();
        for (auto it = cnt.rbegin();
             ok && (n - 1 - ans.size()) && it != rend;
             ++ it)
            while (it->second)
            {
                auto pair = now - it->first;
                if (!cnt.count(pair) || !cnt[pair])
                {ok = false; break;}
                -- cnt[pair], -- it->second;
                ans.push({pair, it->first});
                now = max(it->first, pair);
            }
        return ok;
    };
    while (t --)
    {
        int n = scanner.nextInt();
        const int nn = n * 2;
        for (int i = 1; i <= nn; ++ i)
            a[i] = scanner.nextInt();
        sort(a + 1, a + 1 + nn);
        bool ok = false; int mate;
        for (int i = 1; !ok && i < nn; ++ i)
            ok |= tryTo(nn, mate = a[i], n);
        if (!ok) {puts("NO"); continue;}
        puts("YES");
        println(mate + a[nn]);
        print(mate, ' ', a[nn], '\n');
        while (!ans.empty())
        {
            auto [x, y] = ans.front();
            print(x, ' ', y, '\n');
            ans.pop();
        }
    }
    return 0;
}