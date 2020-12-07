/**
 *
 * 做法就和你自己想象的那样，斜方向分成三类点
 * 但是接下来的做法并不是让你去硬找办法：
 * 
 * - 首先，我们意识到每一个三连都包含了三类点中的一种
 * - 因此，只要替换掉三类中的任何一类点，就可以保证不出现三连
 * 
 * 所以只需要统计三类点的个数，然后选择一个最佳方案就行
 * 显然，最佳方案一定是小于 k / 3 的
 * 
 * 虽然最后还是前面代码写傻逼了，但是还是题解的代码更加优雅
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

const int N = 320;
char m[N][N];

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
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            scanner(m[i] + 1);
        vector<pair<int, int>> x[3], o[3];
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                if (m[i][j] == 'X')
                    x[(i + j) % 3].emplace_back(i, j);   
                else if (m[i][j] == 'O')
                    o[(i + j) % 3].emplace_back(i, j);
        const int k = x[0].size() + x[1].size() + x[2].size()
                 + o[0].size() + o[1].size() + o[2].size();
        const int lim = k / 3;         
        for (int ii = 0; ii < 3; ++ ii)
            for (int jj = 0; jj < 3; ++ jj)
                if (ii != jj && x[ii].size() + o[jj].size() <= lim)
                {
                    for (auto [i, j] : x[ii]) m[i][j] = 'O';
                    for (auto [i, j] : o[jj]) m[i][j] = 'X';
                    goto OUTPUT;
                }
        OUTPUT:
        for (int i = 1; i <= n; ++ i) puts(m[i] + 1);        
    }
    return 0;
}