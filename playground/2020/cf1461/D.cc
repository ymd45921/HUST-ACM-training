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

#if 0
#define eprintf(x...) fprintf(stderr, x)
#define eputs(str) fputs(str, stderr), fputc('\n', stderr)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#define $(...) __VA_ARGS__;
#else
#define eprintf(...)
#define eputs(...)
#define watch(...)
#define $(...)
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
int a[N];
vector<longs> sum;
const char yes[] = "Yes", no[] = "No";

namespace SegTree
{
    const int N = 4 * ::N;
    longs node[N];

    longs build()
    {
        const function<longs(int, int, int)> recur =
                [&](int i, int l, int r) -> longs
        {
            if (l < r)
            {
                int mid = (l + r) / 2;
                auto ll = recur(i * 2, l, mid);
                auto rr = recur(i * 2 + 1, mid + 1, r);
                node[i] = ll + rr;
            } else node[i] = sum[l];
            $(cerr << "[" << l << ", " << r << "] = " << node[i] << endl);
            return node[i];
        };
        return recur(1, 0, sum.size() - 1);
    }

    longs query(int lb, int rb)
    {
        const function<longs(int, int, int)> recur =
                [&](int i, int l, int r) -> longs
        {
            if (lb <= l && rb >= r) return node[i];
            else
            {
                int mid = (l + r) / 2;
                longs val = 0;
                if (rb > mid)
                    val += recur(i * 2 + 1, mid + 1, r);
                if (lb <= mid)
                    val += recur(i * 2, l, mid);
                return val;
            }
        };
        return recur(1, 0, sum.size() - 1);
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt(), n, q;
    while (t --)
    {
        scanner(n, q);
        map<int, int> cnt;
        for (int i = 1; i <= n; ++ i)
            a[i] = scanner.nextInt(),
            ++ cnt[a[i]];
        sum.clear(); int cur = 0;
        unordered_map<int, int> trans;
        for (auto [x, t] : cnt)
            sum.push_back((longs)x * t),
            trans[x] = cur ++;
        SegTree::build();
        queue<pair<int, int>> que;
        unordered_set<longs> ans;
        que.push({cnt.begin()->first, (--cnt.end())->first});
        cnt[0] = cnt[N] = 0;
        while (!que.empty())
        {
            auto [l, r] = que.front();
            que.pop();
            if (l == r)
            {
                auto ind = trans[l];
                auto sec = SegTree::query(ind, ind);
                ans.insert(sec);
                watch(l, ind, sec);
                continue;
            }
            int mid = (l + r) / 2;
            auto it = cnt.upper_bound(mid);
            int tmp = it->first;
            if (tmp <= r) que.push({tmp, r});
            tmp = (-- it)->first;
            if (tmp >= l) que.push({l, tmp});
            auto lb = trans[l], rb = trans[r];
            auto sec = SegTree::query(lb, rb);
            ans.insert(sec);
            watch(l, r, lb, rb, sec);
        }
        while (q --)
        {
            int s = scanner.nextInt();
            println(ans.count(s) ? yes : no);
        }
    }
    return 0;
}