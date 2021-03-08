/**
 *
 * CF 编译器竟然没有 typeof
 * 
 * Trie 树这样写不是很行，，MLE 了
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
    template <class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;

#define $$ fastRead,
#define int$(...) int __VA_ARGS__; $$ __VA_ARGS__
#define i64$(...) longs __VA_ARGS__; $$ __VA_ARGS__
#define lll$(...) lll __VA_ARGS__; $$ __VA_ARGS__
#define countDown$(T) int$(T); while (T --)

const int N = 5050;
int a[N], cache[N], pos[N], tmp[N];

namespace Trie
{
    using node = unordered_map<int, int>;
    using string_t = const int *const;
    const int N = ::N * ::N;
    bitset<N> match;
    vector<node> go;
    int tot = 0;

    void clear()
    {
        go.clear(); go.emplace_back();
        match.reset(); tot = 0;
    }

    void insert(const string_t &s, int n)
    {
        int u = 0;
        for (int i = 0, id = s[i];
             i < n; id = s[++ i])
        {
            if (go[u][id]) u = go[u][id];
            else
                u = go[u][id] = ++ tot,
                go.emplace_back();
            match[u] = true;
        }
    }

    bool count(const string_t &s, int n)
    {
        int u = 0;
        for (int i = 0, id = s[i];
             i < n; id = s[++ i])
            if (!id) return true;
            else if (go[u].count(id))
                u = go[u][id];
            else return false;
        return true;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    countDown$(T)
    {
        int$(n, q);
        for (int i = 1; i <= n; ++ i)
            $$ a[i];
        int top = 0; Trie::clear();
        memset(pos, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; ++ i)
        {
            if (!pos[a[i]])
                pos[a[i]] = ++ top,
                cache[top] = a[i];
            else
            {
                for (int j = pos[a[i]]; j < top; ++ j)
                    cache[j] = cache[j + 1], -- pos[cache[j]];
                cache[top] = a[i], pos[a[i]] = top;
            }
            for (int j = 0; j < top; ++ j)
                tmp[j] = cache[top - j];
            Trie::insert(tmp, top);
        }
        while (q --)
        {
            int$(m);
            for (int i = 0; i < m; ++ i)
                $$ a[i];
            bool res = Trie::count(a, m);
            puts(res ? "Yes" : "No");
        }
    }
    return 0;
}