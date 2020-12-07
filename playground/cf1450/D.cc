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
const int inf = 0x3f3f3f3f;
int a[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    bitset<N> ans, tmp;
    const auto output = [&](int n)
    {
        for (int i = 1; i <= n; ++ i)
            putchar(ans[i] ? '1' : '0');
        puts("");
    };
    while (t --)
    {
        int n = scanner.nextInt();
        ans.reset(), tmp.reset();
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt(),
            tmp[a[i]] = true;
        if (!tmp[1])
        {
            puts(string(n, '0').c_str());
            continue;
        } else ans[n] = true;
        int mex;
        for (mex = 1; mex <= n; ++ mex)
            if (!tmp[mex]) break;
        ans[1] = (mex == n + 1);
        vector<vector<int>> pos(mex);
        for (int i = 1; i <= n; ++ i)
            if (a[i] < mex) pos[a[i]].push_back(i);
        set<int> smaller{0, n + 1};
        for (int i = 1; i < mex; ++ i)
        {
            int x = n + 1 - i, cnt = 0;
            int r = 0, l = 0;
            for (auto ii : pos[i])
            {
                auto it = smaller.lower_bound(ii);
                auto rr = *it, ll = *(-- it);
                if (rr != r || ll != l)
                {
                    cnt += (rr - ll - x);
                    l = ll, r = rr;
                }
                if (cnt > 1) break;
            }
            if (cnt == 1) ans[x] = true;
            else break;
            if (pos[i].size() > 1) break;
            for (auto ii : pos[i])
                smaller.insert(ii);
        }
        output(n);
    }
    return 0;
}