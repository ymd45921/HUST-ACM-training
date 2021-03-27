/**
 *
 * 真的是很经典的问题，但是也是真的不会（
 *
 * 题解的做法：
 * - 首先，t 一定是由 s 中出现过的字母组成
 * - 从空串开始构建 t；维护还没有使用的字母
 * - 对于这个集合中的字母，每次遍历找到最大的可用的字母，插入末尾
 * - 可用的意思是，在它出现之后的后缀包含剩下的所有字母
 * emmmm，所以？这样做确实挺合理的（
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

const int N = 2e5 + 5;
char s[N], t[N];
vector<int> pos[30];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    const auto suffix =
    [&](char ch, int st)
    {
        auto &p = pos[ch - 'a'];
        auto it = lower_bound(p.begin(), p.end(), st);
        if (it == p.end()) return -1;
        else return *it;
    };
    const auto count =
    [&](int st)
    {
        if (st == -1) return 0;
        int ret = 0;
        for (const auto &ii : pos)
        {
            auto it = lower_bound(ii.begin(), ii.end(), st);
            if (it != ii.end()) ++ ret;
        }
        return ret;
    };
    while (T --)
    {
        scanner(s);
        int n = strlen(s), len = 0;
        set<char> ss(s, s + n);        // 没什么意义，就是练习一下新的写法
        const int siz = ss.size();
        for (int i = 0; i < n; ++ i)
            pos[s[i] - 'a'].push_back(i);
        int st = 0;
        while (len < siz)
        {
            char add = 0;
            for (auto ch : ss)
                if (count(suffix(ch, st)) + len == siz)
                    maximize(add, ch);
            t[len ++] = add;
            st = suffix(add, st) + 1;
            pos[add - 'a'].clear();
            ss.erase(add);
        } t[len] = '\0';
        println(t);
    }
    return 0;
}