/**
 *
 * 不能嗯做？
 * 你妈的，好像确实不能嗯做（
 *
 * 妈的，是我嗯做做错了（
 *
 * 骗数据：我好像和 23rd 不是很过得去==
 * 9
 * 2 4
 * 3 5
 * 5 3
 * 6 6
 * 7 3
 * 8 6
 * 10 1
 * 10 7
 * 10 7
 * 不得不承认，我的做法确实不够严格（
 * 
 * 我真傻，真的；不能旋转当前的，就全塞进去不就得了（
 * 反正我的做法再不能旋转的情况下是严格正确的==
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

const int N = 2e5 + 5;
int ans[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    using info_t = pair<pair<int, int>, int>;
    vector<info_t> wh, hw;
    const function go =
    [](vector<info_t> &arr)
    {
        info_t last, now;
        last.second = now.second = -1;
        now.first.second = 0x7f7f7f7f;
        last.first.second = 0x7fffffff;
        for (auto &ii : arr)
        {
            auto &[size, index] = ii;
            if (size.first > now.first.first)
            {
                if (now.first.second < last.first.second)
                    last = now;
                else assert(now.first.first > last.first.first);
                now = ii;
            }
            if ((size.first > last.first.first &&
                size.second > last.first.second) ||
                (size.second > last.first.first &&
                size.first > last.first.second))
                (ans[index] == -1) && (ans[index] = last.second);
        }
    };
    while (t --)
    {
        int n = scanner.nextInt();
        wh.clear(), hw.clear();
        memset(ans, -1, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; ++ i)
        {
            int h = scanner.nextInt(),
                w = scanner.nextInt();
            hw.emplace_back(make_pair(h, w), i);
            hw.emplace_back(make_pair(w, h), i);
        }
        sort(hw.begin(), hw.end()), go(hw);
        for (int i = 1; i <= n; ++ i)
            print(ans[i], " \n"[i == n]);
    }
    return 0;
}