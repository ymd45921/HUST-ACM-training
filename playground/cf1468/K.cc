/**
 *
 * WA2: 乱搞果然不行（
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

const int N = 5050;
char s[N];
const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};
int xx[N], yy[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    unordered_map<char, int> dict;
    dict['U'] = 0, dict['D'] = 1,
    dict['L'] = 2, dict['R'] = 3;
    while (T --)
    {
        scanner(s + 1);
        int n = strlen(s + 1);
        int x = 0, y = 0;
        for (int i = 1; i <= n; ++ i)
            x += dx[dict[s[i]]],
            y += dy[dict[s[i]]],
            xx[i] = x, yy[i] = y;
        if (x && y) puts("0 0");
        else
        {
            int step = max(abs(x), abs(y));
            int ansX = 0, ansY = 0;
            for (int i = 0; i <= n; ++ i)
            {
                int j = i + step;
                if (j > n) break;
                int x1 = xx[i], y1 = yy[i];
                int x2 = xx[n] - xx[j], y2 = yy[n] - yy[j];
                if (!(x1 + x2) && !(y1 + y2))
                {
                    const char sig = s[i + 1];
                    bool same = true;
                    if (j != n && sig == s[j + 1]) same = false;
                    for (int ii = i + 2; same && ii <= j; ++ ii)
                        if (sig != s[ii]) same = false;
                    if (!same) continue;
                    else
                    {
                        ansX = x1 + dx[dict[sig]];
                        ansY = y1 + dy[dict[sig]];
                        break;
                    }
                }
            }
            print(ansX, ' ', ansY, '\n');
        }
    }

    return 0;
}