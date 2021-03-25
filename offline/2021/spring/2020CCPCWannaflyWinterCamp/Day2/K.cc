/**
 *
 * 哈哈，几把
 * 
 * 相信队友！
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

using char_t = char;
using string_t = const char *const; // string
const int N = 5e5 + 5;

int p[N];
longs f[N];
const longs inf = 0x3f3f3f3f3f3f3f3f;

namespace acAutomaton
{
    const int dict = 26;

    using node = array<int, dict>;
    using id_list = list<int>;
    using callback_t = function<void(bool, int, const id_list &)>;

    node go[N];
    int tot = 0, fail[N], cnt = 0, depth[N];
    int goal[N];
    bitset<N> vis;

    inline int idx(char_t x) {return x - 'a';}

    void clear()
    {
        for (int i = 0; i <= tot; ++ i)
            go[i].fill(0), fail[i] = 0, goal[i] = 0;
        tot = cnt = depth[0] = 0;
    }

    void insert(const string_t &s, int n, int ii)
    {
        int u = 0;
        for (int i = 0, id = idx(s[0]);
             i < n; id = idx(s[++ i]))
        {
            if (!go[u][id]) go[u][id] = ++ tot;
            depth[go[u][id]] = depth[u] + 1;
            u = go[u][id];
        }
        if (!goal[u] || p[ii] < p[goal[u]])
            goal[u] = ii;
    }

    void build()
    {
        queue<int> q;
        for (int id = 0; id < dict; ++ id)
            if (go[0][id]) q.push(go[0][id]);
        while (!q.empty())
        {
            auto u = q.front(); q.pop();
            for (int id = 0; id < dict; ++ id)
                if (go[u][id])
                    fail[go[u][id]] = go[fail[u]][id], q.push(go[u][id]);
                else go[u][id] = go[fail[u]][id];
        }
    }

    void test(const string_t &t, int n)
    {
        int u = 0; vis.reset();
        auto dp = f + 1;
        for (int i = 0; i < n; ++ i)
        {
            int j = u = go[u][idx(t[i])];
            for (; j; j = fail[j])
                if (goal[j])
                    minimize(dp[i], dp[i - depth[j]] + p[goal[j]]);
        }
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
    int n; cin >> n;
    acAutomaton::clear();
    string s, t;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> s >> p[i];
        acAutomaton::insert(s.c_str(), s.length(), i);
    }
    acAutomaton::build();
    cin >> t;
    memset(f, 0x3f, sizeof(longs) * (t.length() + 1));
    f[0] = 0, acAutomaton::test(t.c_str(), t.length());
    println(f[t.length()] >= inf ? -1ll : f[t.length()]);
    return 0;
}