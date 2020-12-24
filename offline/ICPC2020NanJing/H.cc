/**
 *
 * 为什么加了记忆化搜索就能过？
 * 虽然确实打个表就过了，但是估计赛场上会考虑 7 为边界
 * 这样的话就死了（）伏笔消除术 ==
 * 
 * UPD: 设置边界为 7 也可以通过；伏 笔 消 除 术 · 再 临
 * 
 * 但是这个爆搜我也能卡，这是我没想到的
 * 我可能真的不会写代码吧（
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

const longs mod = 1e9 + 7;
const int N = 2e3 + 5, NN = N * N;
longs pow3[NN];
int tmp[N][N], mem[20][20];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt(), n, m;
    pow3[0] = 1;
    for (int i = 1; i < NN; ++ i)
        pow3[i] = pow3[i - 1] * 3 % mod;
    memset(mem, -1, sizeof mem);    
    const auto check = 
    [](int x1, int y1, int x2, int y2)
    {
        return (tmp[x1][y1] == tmp[x1][y2] && tmp[x2][y1] == tmp[x2][y2])
            || (tmp[x1][y1] == tmp[x2][y1] && tmp[x1][y2] == tmp[x2][y2]);
    };
    const function<longs(int, int)> dfs = 
    [&](int x, int y) -> longs
    {
        if (y > m) ++ x, y = 1;
        if (x > n) return 1;
        longs ret = 0;
        for (int k = 0; k < 3; ++ k)
        {
            tmp[x][y] = k;
            bool found = false;
            for (int i = 1; !found && i < x; ++ i)
                for (int j = 1; !found && j < y; ++ j)
                    found |= check(i, j, x, y);
            if (found) continue;
            else ret += dfs(x, y + 1);        
        }
        return ret;
    };
    while (T --)
    {
        n = scanner.nextInt(),
        m = scanner.nextInt();
        if (n > m) swap(n, m);
        if (n == 1) println(0);
        else if (m > 9) println(pow3[n * m]);
        else if (mem[n][m] != -1) println((pow3[n * m] + mod - mem[n][m]) % mod);
        else
        {
            auto exclude = mem[n][m] = dfs(1, 1) % mod;
            println((pow3[n * m] + mod - exclude) % mod);
        }
    }
    return 0;
}