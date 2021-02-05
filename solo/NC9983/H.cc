/**
 *
 * 傻逼吧，模式串 1e6 输出串 2e6
 * 那不就是个模拟*（
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

const int N = 1e6 + 5;
bitset<N> merged;
string expand[] = {"", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
                   "aa", "ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "t",
                   "ba", "bb", "bc", "bd", "be", "bf"};
signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    string s; stringstream ss;
    cin >> s;
    const int n = s.length();
    vector<int> merge;
    for (int i = 0; i < n; ++ i)
        if (s[i] == 'a')
            if (i + 1 < n && s[i + 1] <= 'i')
                merge.push_back(10 + s[++ i] - 'a' + 1),
                merged[merge.size() - 1] = true;
            else merge.push_back(1);
        else if (s[i] == 'b')
            if (i + 1 < n && s[i + 1] <= 'f')
                merge.push_back(20 + s[++ i] - 'a' + 1),
                merged[merge.size() - 1] = true;
            else merge.push_back(2);
        else merge.push_back(s[i] - 'a' + 1);
    int extend = merged.count() > 0 ? 0 : 1;
    for (auto ii : merge)
        if (extend && ii % 10 && ii > 10)
            ss << expand[ii], -- extend;
        else ss << char(ii + 'a' - 1);
    auto out = ss.str();
    if (out.length() > 2e6 || extend) puts("-1");
    else puts(out.c_str());
    return 0;
}