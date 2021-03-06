/**
 *
 * 还是二分
 * 果然还是不会写二分
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

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, second;
    cin >> n;
    cout << "? 1 " << n << endl;
    cin >> second;
    unordered_map<int, int> cache;
    const auto ask =
    [&](int pos)
    {
        if (cache.count(pos))
            return cache[pos];
        else
        {
            int in;
            int l = min(second, pos);
            int r = max(second, pos);
            cout << "? " << l << ' ' << r << endl;
            cin >> in;
            return cache[pos] = in;
        }
    };
    const auto bin =
    [&](int l, int r, bool dir) -> int
    {
        int ll = l, rr = r;
        if (rr == ll) return ll;
        while (ll < rr)
        {
            auto mid = (ll + rr) / 2 + !dir;
            int res = ask(mid);
            if (res == second)
                (dir ? rr : ll) = mid;
            else (dir ? ll : rr) = mid + (dir ? 1 : -1);
        }
        return dir ? rr : ll;
    };
    int ans;
    if (second == 1)
        ans = bin(2, n, true);
    else if (second == n)
        ans = bin(1, n - 1, false);
    else
    {
        cout << "? 1 " << second << endl;
        int tmp; cin >> tmp;
        int ll = 1, rr = n;
        if (tmp == second) rr = second - 1;
        else ll = second + 1;
        ans = bin(ll, rr, tmp != second);
    }
    cout << "! " << ans << endl;
    return 0;
}