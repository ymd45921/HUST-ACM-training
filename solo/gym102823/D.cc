/**
 *
 * 依然是做法正确但是因为缺乏常识导致愚蠢错误的题目
 * 显然，两个码的“距离”不能通过累加求差的方式得出
 * 因为这样做的话，正误差和负误差会相互抵消，这是错误的
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

int popCount(longs x, bitset<64> &bit)
{
    int cnt = 0, now = 0;
    while (x)
    {
        bit[now] = x % 2;
        cnt += bit[now];
        x /= 2, ++ now;
    }
    return cnt;
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    for (int t = 1; t <= T; ++ t)
    {
        longs x, y; scanner(x, y);
        bitset<64> xx, yy;
        popCount(x, xx), popCount(y, yy);
        vector<int> oddX, evenX, oddY, evenY;
        int ans = 0;
        for (int i = 0; i < 64; ++ i)
        {
            auto &vecX = (i % 2 ? oddX : evenX);
            auto &vecY = (i % 2 ? oddY : evenY);
            if (xx[i]) vecX.push_back(i);
            if (yy[i]) vecY.push_back(i);
        }
        if (oddX.size() == oddY.size() &&
            evenX.size() == evenY.size())
        {
            int sizOdd = oddY.size(),
                sizEven = evenX.size();
            for (int i = 0; i < sizOdd; ++ i)
                ans += abs(oddX[i] - oddY[i]) / 2;
            for (int i = 0; i < sizEven; ++ i)
                ans += abs(evenX[i] - evenY[i]) / 2;        
        } else ans = -1;
        printf("Case %d: ", t);
        println(ans);
    }
    return 0;
}