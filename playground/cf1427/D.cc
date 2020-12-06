/**
 * 
 * 这个题真的有难的不可做吗？我想应该没有吧
 * 
 * [========|i --------|------- i-1|========]
 * 经过操作后变为
 * [========|---- i-1, i ----------|========]
 * 连续有序的 pair 增加了；此过程没有拆分任何原连续有序 pair
 *
 * 因为每次操作增加一个连续有序 pair，最多只有 n-1 对
 * 所以 n 次操作之内一定可以完成这个操作
 *
 * 所以伪线性做法到底是什么
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

const int N = 60;
int deck[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        deck[i] = scanner.nextInt();
    const auto apply = [&](vector<int> op)
    {
        assert(op[0] + op[1] + op[2] + op[3] == n);
        vector<int> $1, $2, $3, $4;
        int cur = 1;
        while (op[0] --) $1.push_back(deck[cur ++]);
        while (op[1] --) $2.push_back(deck[cur ++]);
        while (op[2] --) $3.push_back(deck[cur ++]);
        while (op[3] --) $4.push_back(deck[cur ++]);
        cur = 1;
        for (auto &ii : $4) deck[cur ++] = ii;
        for (auto &ii : $3) deck[cur ++] = ii;
        for (auto &ii : $2) deck[cur ++] = ii;
        for (auto &ii : $1) deck[cur ++] = ii;
    };
    vector<vector<int>> ans;
    while (true)
    {
        vector<int> now;
        int i, j, k;
        for (i = 1; i <= n; ++ i)
            if (deck[i] != i) break;
        if (i == n + 1) break;
        now.push_back(i - 1);
        for (j = i + 1; j <= n; ++ j)
            if (deck[j] - deck[j - 1] != 1) break;
        now.push_back(j - i);
        for (k = j; k <= n; ++ k)
            if (deck[k] == deck[i] - 1) break;
        now.push_back(k - j + 1);
        now.push_back(n - k);
        ans.push_back(now), apply(now);
    }
    println(ans.size());
    for (auto &op : ans)
    {
        int cnt = 0;
        for (auto &ii : op)
            if (ii) ++ cnt;
        print(cnt, ' ');
        for (auto &ii : op)
            if (ii) print(ii, ' ');
        puts("");
    }
    return 0;
}