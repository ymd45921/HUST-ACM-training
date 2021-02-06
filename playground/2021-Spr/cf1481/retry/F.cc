/**
 *
 * 首先，设树高 h，那么最好的情况下也有 h+1 答案
 * 再意识到想要达到这个答案，同一层应当赋值一致
 * 令每层的节点数量的数组为 a[]，那么需要大小为 x 的子集
 * 为了检查这样的子集是否存在，需要 dp，这是 n² 的
 *
 * 但考虑到 Σa = n，故 a 中本质不同的数字是 √n 的
 * 因此使用多重背包判断能否凑出 x 实际上是 O(n√n) 的
 *
 * 然后，如果判定了 a[] 不存在大小为 x 的子集：
 * - 那么答案就是 h + 2，比存在的情况下多 1
 * - 为了避免增加更多新句子，要保证非叶子节点同色
 * - 假设现在剩余的层的节点总和是 m，且剩余的颜色无法填充当前层
 *   - 比当前层更低的节点数量总和严格小于当前层
 *   - 剩余的节点中必然至少有 a[i] 个叶子节点
 *   - 因此，剩余的节点中，非叶子节点数量严格小于叶子节点
 *   - 我们一定可以将非叶子节点染成同色
 *   - 这样，就可以保证深度更大的节点产生的串数量不增加
 * - 串的增加的分歧只会出现在叶子节点一层，而这层只会影响当前层
 * 所以，综上所述，字符串数量最多增加 1.
 *
 * 不得不说我离做出这个题目还有一定的距离
 * 且不论考虑到细致的 +1，就算想到了找到子集和为 x
 * 也不知道应当如何构造实际的填写方式
 *
 * ……事实上看懂这种多重背包的写法就花了好多时间（
 * 构造最终的树可以依靠 DP 的全数组留下的信息
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
int p[N], h[N], siz[N], H = 0, last[N], build[N];
vector<int> e[N], layer[N];
bitset<N> dp[500];      // ? 400 RE, 500 is OK ?
char ans[N];

int dfs(int u, int dep)
{
    maximize(H, dep);
    layer[dep].push_back(u);
    siz[u] = 1, h[u] = dep;
    for (auto v : e[u])
        siz[u] += dfs(v, dep + 1);
    return siz[u];
}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt(),
        x = scanner.nextInt();
    for (int i = 2; i <= n; ++ i)
        p[i] = scanner.nextInt(),
        e[p[i]].emplace_back(i);
    dfs(1, 0);
    unordered_map<int, int> tmp;
    for (int i = 0; i <= H; ++ i)
        if (!layer[i].empty())
            ++ tmp[layer[i].size()];
    dp[tmp.size()][0] = true;
    int resA = x, resB = n - resA, kind = tmp.size();
    vector<pair<int, int>> cnt;
    for (auto [k, v] : tmp)
        cnt.emplace_back(k, v);
    for (int ii = kind - 1; ii >= 0; -- ii)     // 这是多重背包的一种写法，也可压缩空间
    {
        const auto [aa, freq] = cnt[ii];
        memset(last, -1, sizeof(int) * aa);
        for (int j = 0, ja = 0; j <= n; ja = (++ j) % aa)
            (dp[ii + 1][j]) && (last[ja] = j),  // passed by last kind of item
            dp[ii][j] = !(last[ja] == -1 || (j - last[ja]) / aa > freq);
    }
    if (dp[0][resA])
    {
        println(H + 1);
        int res = resA;
        for (int i = 0; i < kind; ++ i)
            while (!dp[i + 1][res])
                ++ build[cnt[i].first],
                res -= cnt[i].first;
        fill(ans + 1, ans + 1 + n, 'b');
        for (int i = 0; i <= H; ++ i)
            if (build[layer[i].size()])
            {
                build[layer[i].size()] --;
                for (auto ii : layer[i]) ans[ii] = 'a';
            }
        ans[n + 1] = '\0';
        puts(ans + 1);
    }
    else    // 层内按照子树大小排序，尽可能大子树的染同色
    {       // 可以证明这样能保证非叶子节点同色，变化只出现在叶子
        println(H + 2);
        const auto compare =
        [&](int i, int j) -> bool
        {return siz[i] < siz[j];};
        char A = 'a', B = 'b';
        for (int i = 0; i <= H; ++ i)
        {
            sort(layer[i].begin(), layer[i].end(), compare);
            if (resA < resB) swap(resA, resB), swap(A, B);
            while (!layer[i].empty() && resA > 0)
                ans[layer[i].back()] = A,
                layer[i].pop_back(), -- resA;
            while (!layer[i].empty() && resB > 0)
                ans[layer[i].back()] = B,
                layer[i].pop_back(), -- resB;
        }
        ans[n + 1] = '\0';
        puts(ans + 1);
    }
    return 0;
}