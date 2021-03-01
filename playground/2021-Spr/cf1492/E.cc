/**
 *
 * 这题好恶心…………
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

const int NM = 250005;
int ans[NM], *db[NM];

int method3[][3] = {{1, 1, 0}, {1, 0, 1}, {0, 1, 1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
int method4[][4] = {{1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}, {0, 1, 0, 1}, {0, 0, 1, 1}};

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        m = scanner.nextInt();
    const auto differ =
    [&](vector<int> &ret)
    {
        for (int i = 1; i <= n; ++ i)
        {
            ret.clear();
            for (int j = 1; j <= m; ++ j)
                if (db[i][j] != ans[j])
                    ret.push_back(j);
            if (ret.size() <= 2) continue;
            else return i;
        } return n + 1;
    };
    const auto modify =
    [&](vector<int> &diff, int other)
    {
        vector<array<int, 2>> map(diff.size());
        vector<int> tmp;
        const auto apply =
        [&](int *use, int siz)
        {
            for (int i = 0; i < siz; ++ i)
                ans[diff[i]] = map[i][use[i]];
            int ret = differ(tmp);
            if (ret > n) return 1;
            else if (diff.size() > 4) return -1;
            else return 0;
        };
        for (int i = 0; i < diff.size(); ++ i)
            map[i][0] = db[1][diff[i]],
            map[i][1] = db[other][diff[i]];
        if (diff.size() == 3)
            for (auto use : method3)
                switch (apply(use, 3))
                {
//                    case -1: return false;
                    case 1: return true;
                }
        else for (auto use : method4)
                switch (apply(use, 4))
                {
//                    case -1: return false;
                    case 1: return true;
                }
        return false;
    };
    for (int i = 1; i <= n; ++ i)
    {
        db[i] = new int[m + 1];
        for (int j = 1; j <= m; ++ j)
            db[i][j] = scanner.nextInt();
    }
    memcpy(ans, db[1], sizeof(int) * (n + 1));
    vector<int> diff;
    auto other = differ(diff);
    bool ok = diff.size() <= 4;
    if (other <= n && ok)
    {
        auto ret = modify(diff, other);
        if (!ret) ok = false;
    }
    if (ok)
    {
        puts("Yes");
        for (int i = 1; i <= m; ++ i)
            print(ans[i], " \n"[i == m]);
    } else puts("No");
    return 0;
}