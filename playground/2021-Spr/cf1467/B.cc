/**
 *
 * 细节不慎：因为可以影响三个，所以可能不仅会减少，还会增加
 *
 * 骗了组数据出来才知道自己考虑不周：
 * 2
 * 7
 * 23 16 9 4 14 9 4
 * 9
 * 11 9 23 24 17 15 8 24 1
 * 涉及到检查 spec 就要修改双边界
 * 
 * 所以不如最开始就使用这种方法；详细的讨论很浪费时间（
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

const int N = 3e5 + 5;
int a[N];
bitset<N> is;

#define isHill(i) (a[i] > a[(i) - 1] && a[i] > a[(i) + 1])
#define isValley(i) (a[i] < a[(i) - 1] && a[i] < a[(i) + 1])
#define spec(i) (isHill(i) || isValley(i))

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    vector<int> pos;
    while (T --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt();
        a[0] = a[1], a[n + 1] = a[n], pos.clear();
        for (int i = 2; i < n; ++ i)
            if (spec(i)) pos.push_back(i);
        int cnt = pos.size();
        int reduce = bool(cnt);
        for (int i = 1; i < cnt; ++ i)
            if (pos[i - 1] + 1 == pos[i])
            {
                int tmp = a[pos[i - 1]];
                swap(tmp, a[pos[i]]);
                if (!spec(pos[i] + 1)) reduce = 2;
                swap(tmp, a[pos[i]]);
                tmp = a[pos[i]];
                swap(tmp, a[pos[i - 1]]);
                if (!spec(pos[i - 1] - 1)) reduce = 2;
                swap(tmp, a[pos[i - 1]]);
            }
        for (int i = 2; i < cnt; ++ i)
            if (pos[i - 2] + 2 == pos[i]) reduce = 3;
        println(cnt - reduce);
    }
    return 0;
}