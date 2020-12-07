/**
 *
 * jb 做法
 * 
 * 只能过样例，吐了
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

#if 0
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
int cnt[N][N], n, k;

int countToken(int i, int j)
{
    if (m[i][j] == '.') return 0;
    const auto token = m[i][j];
    bool uu = i - 2 > 0 ? m[i - 2][j] == token : false;
    bool u = i - 1 > 0 ? m[i - 1][j] == token : false;
    bool dd = i + 2 > 0 ? m[i + 2][j] == token : false;
    bool d = i + 1 > 0 ? m[i + 1][j] == token : false;
    bool ll = j - 2 > 0 ? m[i][j - 2] == token : false;
    bool l = j - 1 > 0 ? m[i][j - 1] == token : false;
    bool rr = j + 2 > 0 ? m[i][j + 2] == token : false;
    bool r = j + 1 > 0 ? m[i][j + 1] == token : false;
    return (uu & u) + (dd & d) + (ll & l) + (rr & r) +
            (u & d) + (l & r);
}

void flip(int i, int j)
{
    if (m[i][j] == '.') return;
    m[i][j] = m[i][j] == 'X' ? 'O' : 'X';
}

bool check()
{
    bool pass = true;
    for (int i = 1; pass && i <= n; ++ i)
        for (int j = 1; pass && j <= n; ++ j)
            if (countToken(i, j)) pass = false;
    return pass;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    map<pair<int, int>, bool> tmp;
    const auto apply = [&]
    {
        for (auto &ii : tmp)
            if (ii.second) flip(ii.first.first, ii.first.second);
    };
    const auto count = [&]
    {
        int size = 0;
        for (auto &ii : tmp)
            if (ii.second) ++ size;
        return size;
    };
    while (t --)
    {
        n = scanner.nextInt(), k = 0;
        for (int i = 1; i <= n; ++ i)
            scanner(m[i] + 1);
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                k += m[i][j] != '.',
                cnt[i][j] = countToken(i, j);
        const int lim = k / 3;
        bool found = false;
        for (int o = 0; !found && o < 3; ++ o)
            for (int p = 0; !found && p < 3; ++ p)
        {
            tmp.clear();
            for (int i = 1; i <= n; ++ i)
                for (int j = (i + o) % 3; j <= n; j += 3)
                    if (!j) continue;
                    else if (m[i][j] == 'O' && cnt[i][j])
                        tmp[{i, j}] = !tmp[{i, j}];
            for (int i = 1; i <= n; ++ i)
                for (int j = (3000 - i + p) % 3; j <= n; j += 3)
                    if (!j) continue;
                    else if (m[i][j] == 'X' && cnt[i][j])
                        tmp[{i, j}] = !tmp[{i, j}];
            apply();
            bool pass = check();
            int size = count();
            for (int i = 1; i <= n; ++ i)
                eputs(m[i] + 1);
            watch(size, pass);
            eputs("");
            if (!pass || size > lim) apply();
            else { found = true; break; }
        }
        for (int o = 0; !found && o < 3; ++ o)
            for (int p = 0; !found && p < 3; ++ p)
        {
            tmp.clear();
            for (int i = 1; i <= n; ++ i)
                for (int j = (i + o) % 3; j <= n; j += 3)
                    if (!j) continue;
                    else if (m[i][j] == 'X' && cnt[i][j])
                        tmp[{i, j}] = !tmp[{i, j}];
            for (int i = 1; i <= n; ++ i)
                for (int j = (3000 - i + p) % 3; j <= n; j += 3)
                    if (!j) continue;
                    else if (m[i][j] == 'O' && cnt[i][j])
                        tmp[{i, j}] = !tmp[{i, j}];
            apply();
            bool pass = check();
            int size = count();
            for (int i = 1; i <= n; ++ i)
                eputs(m[i] + 1);
            watch(size, pass);
            eputs("");
            if (!pass || size > lim) apply();
            else { found = true; break; }
        }
        for (int i = 1; i <= n; ++ i)
            puts(m[i] + 1);
    }
    return 0;
}