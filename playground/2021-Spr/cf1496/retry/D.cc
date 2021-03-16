/**
 *
 * 虽然确凿的是要选择山峰，但是博弈却未必在一座山上
 * 如果最长的山坡出现了两次以上：
 * - 那么必定不出现在一座山峰内
 * - 那么后手可以走和先手一样的步数，先手必败
 * 如果最长的山坡只有一座，那么后手可以选择从山脚/+1的位置出发：
 * - 因为这是唯一的最长山坡，所以就算 +1 位置也不会比其他的山坡短
 * - 因此先后手至少可以走一样的步数，先手必败
 * 如果最长的山坡出现了两次：
 * - 如果不出现在一座山峰的两侧，那么和情况一一样
 * - 否则，如果山坡的长度是奇数：
 *   - 先手不能顺着后手的方向走：会被堵死
 *   - 先手不能回避后手的方向走：先手必败
 * - 否则，后手不堵则会被先手堵；堵则不如先手长
 * 因此必胜条件是出现次数为 2 且出现在一座山峰内，坡长偶数
 * 
 * 还不如嗯扫（）
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
#define watch(...) trace(cerr, #__VA_ARGS__, __VA_ARGS__)
#define let(os, ...) trace(os, #__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#define let(os, ...)
#endif

template <class printable>
void trace(ostream &os, const char *name, printable &&value)
{os << name << " = " << value << endl;}
template <class printable, class ...args>
void trace(ostream &os, const char *names, printable &&value, args &&...list)
{
    const char *separate = strchr(names + 1, ',');
    os.write(names, separate - names) << " = " << value << ',';
    trace(os, separate + 1, list...);
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
    template<class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;
#define $$ fastRead,

const int N = 1e5 + 5;
int a[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    set<int> top, valley;
    valley.insert(1), valley.insert(n);
    for (int i = 2; i < n; ++ i)
        if (sgn(a[i] - a[i - 1]) ==
            sgn(a[i + 1] - a[i]))
            continue;
        else if (sgn(a[i] - a[i - 1]) > 0)
            top.insert(i);
        else valley.insert(i);
    bool found = false;
    int longest = 0;
    /*const auto validator =
    [&](int l, int r)
    {
        assert(l > 0 && r > 0);
        if (l == r)
            if (l > longest)
                found = !(l % 2), longest = l;
            else found = false;
        else if (max(l, r) >= longest)
            found = false, maximize(longest, l, r);
        else return;
    };*/
    map<int, pair<int, bool>> cnt;
    const auto counter =
    [&](int l, int r)
    {
        ++ cnt[l].first, ++ cnt[r].first;
        if (l == r) cnt[l].second = true;
    };
    for (auto ii : top)
    {
        auto it = valley.upper_bound(ii);
        int rr = *it, ll = *--it;
        auto r = rr - ii, l = ii - ll;
        counter(l, r);
    }
    auto lb = ++ valley.begin(), ls = valley.begin();
    auto rb = ++ valley.rbegin(), rs = valley.rbegin();
    if (!top.empty())
    {
        auto lt = top.begin();
        auto rt = top.rbegin();
        if (*rt < *rb) ++ cnt[*rs - *rb].first;
        if (*lt > *lb) ++ cnt[*lb - *ls].first;
    }
    found = !cnt.empty()
            && !(cnt.rbegin()->first % 2)
            && (cnt.rbegin()->second.first == 2)
            && cnt.rbegin()->second.second;
//    if (n == 88888) let(cout, longest, cnt.rbegin()->first, cnt.rbegin()->second.first, cnt.rbegin()->second.second);
    println((int)found);
    return 0;
}