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

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, t, g;
    cin >> n;
    using team = tuple<int, int, int, int, int, int, int>;
    vector<string> ss;
    unordered_map<string, int> val;
    vector<team> cnt;
    const auto init = [&]
    {
        ss.clear(), val.clear();
        cnt.clear();
    };
    const auto cmp = []
    (const team &a, const team &b) -> bool
    {
        auto &[ano, a1, a0, aw, at, al, apt] = a;
        auto &[bno, b1, b0, bw, bt, bl, bpt] = b;
        auto ad = a1 - a0, bd = b1 - b0;
        if (apt != bpt) return apt > bpt;
        else if (ad != bd) return ad > bd;
        else if (a1 != b1) return a1 > b1;
        else return ano < bno;
    };
    string s, a, b; int aa, bb;
    for (int i = 1; i <= n; ++ i)
    {
        init();
        cin >> t >> g;
        while (t --)
        {
            cin >> s;
            ss.push_back(s);
        }
        sort(ss.begin(), ss.end());
        t = ss.size();
        for (int i = 0; i < t; ++ i)
            val[ss[i]] = i,
            cnt.emplace_back(i, 0, 0, 0, 0, 0, 0);    
        while (g --)
        {
            cin >> a >> aa
                >> b >> bb;
            int aaa = val[a], bbb = val[b];
            auto &[ano, a1, a0, aw, at, al, apt] = cnt[aaa];
            auto &[bno, b1, b0, bw, bt, bl, bpt] = cnt[bbb];
            a1 += aa, b0 += aa, b1 += bb, a0 += bb;
            if (aa > bb)
            {
                ++ aw, ++ bl;
                apt += 3;
            }
            else if (aa < bb)
            {
                ++ bw, ++ al;
                bpt += 3;
            }
            else ++ at, ++ bt, ++ apt, ++ bpt;
        }   
        sort(cnt.begin(), cnt.end(), cmp);
        // reverse(cnt.begin(), cnt.end());
        cout << "Group " << i << ":\n";
        for (auto &ii : cnt)
        {
            auto [no, _1, _0, win, tie, lose, pt] = ii;
            cout << ss[no] << ' ' << pt << ' ' << win << ' '
                 << lose << ' ' << tie << ' ' << _1 << ' '
                 << _0 << endl;
        }
        cout << endl;
    }
    return 0;
}