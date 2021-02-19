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

ostream &operator <<(ostream &os, const vector<int> &vec)
{
    os << "["; bool comma = false;
    for (auto ii : vec) os << (comma ? ", " : "") << ii, comma = true;
    return os << "]" << flush;
}

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

template <class T>
void buildKMP(const T *arr, vector<int> &kmp, int length)
{
    kmp.resize(length + 1);
    int i = 0, j = kmp[0] = -1;
    while(i < length)
        if(-1 == j || arr[i] == arr[j])
            kmp[++ i] = ++ j;
        else j = kmp[j];
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    string s, t;
    vector<int> kmp, pref, lpx;
    cin >> s >> t;
//    t.append(s.length(), ' ');
    pref.resize(t.length() + 1);
    lpx.resize(t.length() + 1);
    buildKMP(s.c_str(), kmp, s.length());
    int i = 0, j = 0, cnt = 0;
    int pl = s.length(), tl = t.length();
    while (i < tl)
        if (j == -1 || t[i] == s[j])
        {
            ++ i, ++ j; lpx[i] = j;
            if (j != pl) continue;
            ++ cnt, j = kmp[j];
        }
        else j = kmp[j];
    for (int ii = tl; ii >= 0; -- ii)
    {
        maximize(pref[ii - lpx[ii]], lpx[ii]);
        int tmp = kmp[lpx[ii]];
        while (tmp > 0 && pref[ii - tmp] < tmp)
            pref[ii - tmp] = tmp, tmp = kmp[tmp];
    }
    longs ans = 0; watch(pref);
    int lim = min(pref[0], tl - 1);
    for (int ii = 1; ii <= lim; ++ ii)
        ans += min(pref[ii], tl - ii);
    println(ans);
    return 0;
}