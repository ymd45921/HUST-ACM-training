/**
 *
 * 硬要说，模型大家都会建，肯定是建立偏序然后拓扑排序
 * 但是就是没有想到什么办法快速匹配字符串
 *
 * 明明前不久就学习了字符串专题，但为什么不会用 Trie 呢
 *
 * 但是 Trie 对于这个题目还是太高级了，还有一些办法
 * 比如仅仅使用一个数组进行直接排序，枚举所有包含通配符的情况
 * 进行最多 2^k 次的二分查找，就可以找到所有的情况
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

const int N = 1e5 + 5;

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m, k, mt;
    string tmp;
    map<string, int> p;
    cin >> n >> m >> k;
    vector<vector<int>> g(n + 1);
    vector<int> in(n + 1);
    const uint kk = 1u << (uint)k;
    for (int i = 1; i <= n; ++ i)
        cin >> tmp, p[tmp] = i;
    vector<int> other;
    while (m --)
    {
        cin >> tmp >> mt;
        other.clear();
        bool found = false;
        for (uint i = 0; i < kk; ++ i)
        {
            auto x = tmp;
            for (uint ii = 0; ii < k; ++ ii)
                if (i & (1u << ii)) x[ii] = '_';
            if (p.count(x))
                if (p[x] == mt) found = true;
                else other.push_back(p[x]);
            else continue;
        }
        if (!found) return puts("NO"), 0;
        for (auto v : other) g[mt].push_back(v), ++ in[v];
    }
    vector<int> ans;
    queue<int> q;
    bitset<N> vis;
    for (int i = 1; i <= n; ++ i)
        if (!in[i])
            vis[i] = true,
            ans.push_back(i),
            q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto v : g[u])
            if (!-- in[v])
            {
                if (vis[v]) return puts("NO"), 0;
                else vis[v] = true;
                ans.push_back(v);
                q.push(v);
            }
    }
    if (ans.size() != n) return puts("NO"), 0;
    puts("YES");
    for (auto ii : ans) print(ii, ' ');
    return 0;
}