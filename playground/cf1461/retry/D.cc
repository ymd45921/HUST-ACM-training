/**
 *
 * 本来说是线段树写傻逼了导致没有过==
 *
 * 但是仔细想想这真的犯不着线段树啊操你妈（
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

const int N = 1e5 + 5;
int a[N];
longs sum[N];

signed main()
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
        int n, q;
        scanner(n, q);
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        sort(a + 1, a + 1 + n);
        vector<pair<int, int>> map;
        for (int i = 1, ii = a[i]; i <= n; ii = a[++ i])
            if (map.empty() || map.back().first != ii)
                map.emplace_back(ii, 1);
            else ++ map.back().second;
        unordered_map<int, int> index;
        for (int cur = 1; cur <= map.size(); ++ cur)
            sum[cur] = (longs)map[cur - 1].first * map[cur - 1].second,
            index[map[cur - 1].first] = cur;
        for (int i = 1; i < map.size(); ++ i)
            sum[i + 1] += sum[i];
        unordered_set<longs> ans;
        queue<pair<int, int>> que;
        que.push({map[0].first, map.back().first});
        while (!que.empty())
        {
            auto [ll, rr] = que.front();
            que.pop();
            int l = index[ll] - 1, r = index[rr];
            ans.insert(sum[r] - sum[l]);
            if (ll == rr) continue;
            auto mid = make_pair((ll + rr) / 2, INT32_MAX);
            int off = upper_bound(map.begin(), map.end(), mid) - map.begin();
            que.push({ll, map[off - 1].first}), que.push({map[off].first, rr});
        }
        while (q --)
        {
            int s = scanner.nextInt();
            if (ans.count(s)) println("Yes");
            else println("No");
        }
    }
    return 0;
}