/**
 *
 * 模拟都不会？
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

const int N = 1e5 + 5;
bitset<N> can, in;
int first[N], second[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    vector<pair<int, int>> monster;
    priority_queue<pair<int, int>> heap;
    map<int, int> tmp;
    while (T --)
    {
        int n = scanner.nextInt();
        memset(first, 0, sizeof(int) * (n + 1));
        memset(second, 0, sizeof(int) * (n + 1));
        for (int i = 1; i <= n; ++ i)
            monster.emplace_back(
                scanner.nextInt(),
                scanner.nextInt());
        sort(monster.begin(), monster.end());
        for (auto [t, k] : monster)
            if (!first[k]) first[k] = t;
            else if (!second[k]) second[k] = t;
            else continue;
        int last = 0, handle = 0, ans = -1;
        for (auto [t, k] : monster)
        {
            if (t > last)
            {
                int times = t - last;
                while (times --)
                {
                    handle = max(0, handle - 1);
                    if (!heap.empty())
                        can[heap.top().second] = true,
                        handle += tmp[heap.top().second],
                        heap.pop();
                    else handle = max(0, handle - 1);
                    ++ ans;
                }
                last = t;
            }
            if (can[k]) ++ handle;
            else if (!in[k]) heap.push({-second[k], k}), in[k] = true;
            else ++ tmp[k];
        }
        while (!heap.empty())
        {
            handle = max(0, handle - 1);
            can[heap.top().second] = true;
            handle += tmp[heap.top().second];
            heap.pop(); ++ ans;
        }
        ans += (handle + 1) / 2;
        println(ans);
        tmp.clear(), in.reset();
        can.reset(), monster.clear();
    }
    return 0;
}