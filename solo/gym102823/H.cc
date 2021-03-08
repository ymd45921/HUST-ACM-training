/**
 *
 * 虽然可以说有思路，但是细节上的处理还是不到位
 * 算了，这个比我想得有一定的思维复杂度
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

const int N = 1e4 + 5;
char s1[N], s2[N], ss[N]; 

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    for (int tt = 1; tt <= t; ++ tt)
    {
        scanner(s1, s2);
        const int n = strlen(s1);
        vector<int> diff;
        for (int i = 0; i < n; ++ i)
            if (s1[i] == s2[i]) ss[i] = 'a';
            else diff.push_back(i);
        int hm1 = 0, hm2 = 0, siz = diff.size();
        for (auto ii : diff) 
        {
            ss[ii] = 'a';
            if (s1[ii] != 'a') ++ hm1;
            if (s2[ii] != 'a') ++ hm2;
        }
        int delta = hm1 - hm2;  
        for (int i = siz - 1; i >= 0; -- i)
        {
            if (!delta) break;
            const int ii = diff[i];
            char ll = s1[ii], rr = s2[ii];
            int signum = 1;
            if (ll > rr) swap(ll, rr), signum = -1;
            delta *= signum;
            if (ll == 'a')
                if (rr == 'b')
                    if (delta <= -2) ss[ii] = rr, delta += 2;
                    else ss[ii] = 'c', delta += 1;
                else if (delta <= -2) ss[ii] = rr, delta += 2;
                else ss[ii] = 'b', delta += 1;
            else if (delta > 0)
                ss[ii] = ll, -- delta;
            else ss[ii] = rr, ++ delta;    
            delta *= signum;
        }
        ss[n] = '\0';
        printf("Case %d: ", tt);
        println(ss);
    }
    return 0;
}