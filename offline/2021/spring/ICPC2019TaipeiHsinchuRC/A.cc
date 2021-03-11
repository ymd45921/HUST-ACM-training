/**
 *
 *
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

int g[10][10], leng[20];
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
const int inf = 0x3f3f3f3f;

bool validator(int x, int y)
{return x > 0 && y > 0 && x < 7 && y < 7;}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    for (int i = 1; i <= 6; ++ i)
        for (int j = 1; j <= 6; ++ j)
            g[i][j] = scanner.nextInt();
    for (int i = 1; i <= 6; ++ i)   
        for (int j = 1; j <= 6; ++ j)
            for (int k = 0; k < 4; ++ k)
                for (int l = 1; l < 3; ++ l)
                {
                    int xx = i + dx[k] * l,
                        yy = j + dy[k] * l;
                    if (!validator(xx, yy)) continue;
                    else if (g[xx][yy] == g[i][j])
                        maximize(leng[g[i][j]], l + 1);    
                }        
    int steps = 0;
    const auto least = [&]
    {
        for (int i = 1; i <= 6; ++ i) 
            if (g[3][i] == 1) return 7 - i;
        return inf;    
    };
    const function<bool(int)> dfs = 
    [&](int done) -> bool
    {
        auto aa = least();
        if (aa + done > steps) return false;
        else if (aa == leng[1]) return true;
        for (int i = 1; i <= 6; ++ i)
            for (int j = 1; j <= 6; ++ j)
                if (g[i][j]) for (int k = 0; k < 4; ++ k)
                {
                    const int now = g[i][j];
                    int xx = i + dx[k] * (leng[now] - 1),
                        yy = j + dy[k] * (leng[now] - 1);
                    if (!validator(xx, yy) || 
                        g[xx][yy] != g[i][j]) 
                        continue;
                    int nx = i - dx[k], ny = j - dy[k];
                    if (validator(nx, ny) && !g[nx][ny])
                    {
                        g[nx][ny] = now, g[xx][yy] = 0;
                        if (dfs(done + 1)) return true;
                        g[nx][ny] = 0, g[xx][yy] = now;
                    }  
                }
        return false;         
    };    
    while (steps <= 10)
        if (dfs(0)) break;
        else ++ steps;
    println(steps > 10 ? -1 : steps);    
    return 0;
}