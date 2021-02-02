/**
 *
 * 通常做法：DP，平方时间
 * 优化：使用线段树优化第二维
 * 妈的，到头来还是得看洛谷
 *
 * 朴素做法：
 * - 令 f[i] 代表了前 i 个灯笼可以保证的最长前缀
 * - 那么 f[i] + 1 是照耀不到的，我们假设右侧 j 向左看可以照耀这个
 * - 那么，[f[i] + 1, j] 已经全部被照耀了，[i, j) 的灯笼只需要向右看
 * - 如果 f[i] > i，那么将第 i 个灯笼向右看来延长 f[i]
 * 官方题解就是这么说的，我觉得实在不是很能让人看懂（
 * 形式化的说：
 * - f[i] = f[i - 1] 一定可以转移
 * - 如果 f[i - 1] >= i，说明 i 可以被前面的灯照到
 *   - 此时，可以使第 i 个灯向右边照亮更远的灯，这一定可行
 *   - 这样，就可以进行转移：max(f[i - 1], i + p[i]) -> f[i]
 * - 第 i 个灯总是可以向左看，可能可以和左侧组成连续区间
 *   - 设 t < i，如果 f[t] >= i - p[i] - 1，则说明可以组成前缀
 *   - 找到最小的 t，这样就可以使得 (t, i) 所有的灯都照向右侧
 *   - 这样，就可以进行转移：max(i - 1, x + p[x]) -> f[i]
 * - 显然，f[i] 是递增的，找到最小的 t 可以使用二分法
 * - 因此，只有在向左看的时候需要维护 RMQ 以快速回答转移值
 * 本质上是 RMQ 问题，可以使用 ST 表等进行维护
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
const int inf = 1e9 + 7;
int p[N], f[N], L[N], R[N];
int suc[N];
char ans[N];

template <class T>
class seg_tree
{
    using merge_t = function<T(T&, T&)>;
    int siz;
    vector<T> t;
    merge_t merge;
    T init;

    void fix(int id)
    {t[id] = merge(t[id * 2 + 1], t[id * 2 + 2]);}

    void build(int id, int l, int r)
    {
        if (l + 1 == r) { t[id] = init; return; }
        int m = (l + r) / 2;
        build(id * 2 + 1, l, m);
        build(id * 2 + 2, m, r);
        fix(id);
    }

    void update(int id, int l, int r, int pos, T val)
    {
        if (l + 1 == r)
        {
            t[id] = merge(t[id], val);
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) update(id * 2 + 1, l, m, pos, val);
        else update(id * 2 + 2, m, r, pos, val);
        fix(id);
    }

    T query(int id, int l, int r, int ll, int rr)
    {
        if (ll >= rr) return init;
        else if (ll == l && rr == r) return t[id];
        int m = (l + r) / 2;
        auto lv = query(id * 2 + 1, l, m, ll, min(rr, m));
        auto rv = query(id * 2 + 2, m, r, max(m, ll), rr);
        return merge(lv, rv);
    }

public:
    explicit seg_tree(int n = 0, T default_v = 0,
                      merge_t m = [](T &a, T &b){return max(a, b);})
    : siz(n), init(default_v), merge(std::move(m)) {t.resize(4 * n);}

    void resize(int n) {siz = n; t.resize(4 * n);}

    void build() {return build(0, 0, siz + 1);}

    void update(int pos, T val) {update(0, 0, siz + 1, pos, val);}

    T query(int ll, int rr) {return query(0, 0, siz + 1, ll, rr);}
};

const auto max_merge =
[](int &a, int &b)
{return max(a, b);};

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int T = scanner.nextInt();
    while (T --)
    {
        int n = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            p[i] = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            L[i] = i - p[i], R[i] = i + p[i];
        f[0] = f[1] = 0, suc[1] = 1;
        seg_tree<int> rmq(n + 1, -inf, max_merge);
        rmq.build();
        for (int i = 1; i <= n; ++ i)
            rmq.update(i, R[i]);
        for (int i = 2; i <= n; ++ i)
            if (!p[i])
            {
                f[i] = f[i - 1];
                suc[i] = i;
            }
            else
            {
                auto t = lower_bound(f, f + i, L[i] - 1) - f;
                suc[i] = t;
                if (t != i)
                {
                    f[i] = max(i - 1, rmq.query((int)t + 1, i));
                    if (f[i - 1] > f[i]) suc[i] = i, f[i] = f[i - 1];
                    if (f[i - 1] >= i && R[i] > f[i]) f[i] = R[i], suc[i] = i;
                }
                else f[i] = f[i - 1];
            }
        if (f[n] < n) puts("NO");
        else
        {
            puts("YES");
            int now = n;
            while (now)
                if (suc[now] != now)
                {
                    ans[now] = 'L';
                    fill(ans + suc[now] + 1, ans + now, 'R');
                    now = suc[now];
                } else ans[now --] = 'R';
            ans[n + 1] = '\0', puts(ans + 1);
        }
    }
    return 0;
}