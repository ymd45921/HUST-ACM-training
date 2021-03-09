/**
 *
 * 怎么说呢，首先显然是要保留一个前缀
 * 然后修改前缀后的第一个位置之后，后面就无所谓了
 * 所以不需要被后面的位置所束缚
 * 
 * 问题转化为对于一个前缀，给定字符串总长：
 * - 能否以这个前缀为基础，构造出一个美丽的字符串
 * - 如果能，那么就把前缀所缺少的字母补齐，然后填 a 即可
 * - 当然，后缀除了修改的位置之外的其他位置都需排序
 * 这样就可以做出这个题目了；嗯模拟还是太复杂了一点（
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
void print(const char *s) {fputs(s, stdout);}
void print(char *s) {fputs(s, stdout);}
void print(string &s) {print(s.c_str());}
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

struct fast_read
{
    template<class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;
#define $$ fastRead,

const int N = 1e5 + 5;
int cnt[30];
char s[N], app[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt(), n, k, need;
    const auto stillNeed =
    [&](int x) {return (k - x % k) % k;};
    const auto alter =
    [&](char ch, int delta)
    {
        need -= stillNeed(cnt[ch - 'a']);
        cnt[ch - 'a'] += delta;
        need += stillNeed(cnt[ch - 'a']);
    };
    while (T --)
    {
        $$ n, k;
        if (n % k) {println(-1); continue;}
        memset(cnt, 0, sizeof cnt);
        $$ s;
        for (int i = 0; i < n; ++ i)
            ++ cnt[s[i] - 'a'];
        for (int i = need = 0; i < 26; ++ i)
            need += stillNeed(cnt[i]);
        if (!need) {println(s); continue;}
        for (int i = n - 1; i >= 0; -- i)
        {
            alter(s[i], -1);
            for (auto alt = s[i] + 1; alt <= 'z'; ++ alt)
            {
                alter(alt, +1);
                if (i + need < n)
                {
                    for (int j = 0; j < i; ++ j)
                        print(s[j]);
                    print((char)alt);
                    int cur = 0, res = n - i - 1;
                    for (char ch = 'a'; ch <= 'z'; ++ ch)
                    {
                        int m = stillNeed(cnt[ch - 'a']);
                        res -= m;
                        while (m --) app[cur ++] = ch;
                    }
                    while (res --) app[cur ++] = 'a';
                    app[cur] = 0;
                    sort(app, app + cur);
                    println(app);
                    goto complete;
                }
                alter(alt, -1);
            }
        }
        complete: continue;
    }
    return 0;
}