/**
 *
 * 这就是暴力🐎
 * 
 * 还是讨论没有讨论清楚：
 * - 当不匹配的位置是 3 的时候，是有一个位置可以随意匹配的，而不是二选一
 * - 这个空位可以用通配符先代替：当检查再次出现冲突时填充
 * - 当不匹配的位置时 4 的时候，情况是固定的，但是还是可以设置一个通配符
 * - 这种情况下，这个通配符理论会自动填充一个合理的值（也未必二选一
 * 因此，并不需要专门写两个函数来处理这种事情，可以合二为一
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

struct fastRead
{
    template<class name>
    fastRead operator, (name &x)
    {scanner(x); return fastRead{};}
} in;

const int N = 250005;
const int wildcard = -1;
vector<int> a[N];
int ans[N], tmp[N];

vector<int> diff(int t, int n)
{
    vector<int> differ;
    for (int i = 1; i <= n; ++ i)
        if (ans[i] != a[t][i])
            differ.push_back(i);
    return differ;
}

bool check(int* arr, int n, int m)
{
    for (int i = 1; i <= n; ++ i)
    {
        int cnt = 0, pos = -1;
        for (int j = 1; j <= m; ++ j)
            a[i][j] != arr[j] && ++ cnt,
            wildcard == arr[j] && (pos = j);        // Only 1 wildcard
        if (cnt > 3) return false;
        else if (3 == cnt)
            if (-1 != pos) arr[pos] = a[i][pos];
            else return false;
        else continue;
    }
    return true;
}

void answer(bool ok, int *arr = nullptr, int m = 0)
{
    if (!ok) return void(puts("No"));
    else puts("Yes");
    for (int i = 1; i <= m; ++ i)
        print(abs(arr[i]), " \n"[m == i]);
}

void copy(int *arr, int id, int m)
{for (int i = 1; i <= m; ++ i) arr[i] = a[id][i];}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, m;
    in, n, m;
    for (int i = 1; i <= n; ++ i)
    {
        a[i].resize(m + 1);
        for (int j = 1; j <= m; ++ j) in, a[i][j];
    }
    copy(ans, 1, m);
    auto maxDiff = make_pair(0, 0);
    for (int i = 1; i <= n; ++ i)
    {
        int res = diff(i, m).size();
        maximize(maxDiff, {res, i});
    }
    if (maxDiff.first <= 2) answer(true, ans, m);
    else if (maxDiff.first > 4) answer(false);
    else
    {
        auto delta = diff(maxDiff.second, m);
        auto siz = maxDiff.first;
        for (int i = 0; i < siz; ++ i)
            for (int j = i + 1; j < siz; ++ j)
            {
                copy(tmp, maxDiff.second, m);
                int pos1 = delta[i], pos2 = delta[j];
                tmp[pos1] = wildcard, tmp[pos2] = ans[pos2];
                if (check(tmp, n, m)) return answer(true, tmp, m), 0;
                tmp[pos1] = ans[pos1], tmp[pos2] = wildcard;
                if (check(tmp, n, m)) return answer(true, tmp, m), 0;
            }
        answer(false);
    }
    return 0;
}