/**
 *
 * 贪心只考虑出边入边，可能无法成大环
 * 
 * 哎，还是想复杂了；排序是真的可以：
 * - 虽然说顺坡而下是免费的，但是我们未必亦步亦趋
 * - 所以问题就变成了我应该怎么回到顶点
 * - 因为有了减免程度，所以有些上坡也是免费的
 * - 反正下坡免费，所以只需要考虑最大的免费上坡就行
 * - 然后再建立到收费最小的收费上坡的边
 *   - 首先，因为有减免额度的存在，直接上坡不如中转
 *   - 因为中转的话可以吃到中转节点的免费额度
 *   - 但是这条边仍然存在，因为可能吃到了部分的免费额度
 * - 这样的建图，就可以求出最小的上坡费用了
 * 当然，这也不是这个题目的唯一思路：
 * 同样是基于排过序的数列，从高处走向低处是免费的
 * - 首先我们设法统计到达每个位置的最少费用，最低的位置是 0
 * - 这个费用可以有此前的最大优惠的位置出发到达此处的花费
 * - 加上从最低位置到达这个位置的最少花费来求出
 * - 因此，我们可以递推式地维护这个结果，求出所有位置的最少花费
 * - 又因为，每个位置都要到达，所以把所有位置的这个加上答案
 * 因为还是排序的序列，所以我们还是要从最低点回到最高点
 * 因为有优惠券的存在，所以分步走肯定还是要比直接跳上来要优的
 * 第一种思路就是很简单的基于这种情况建图，然后找到到达顶部的最短路
 * 第二种思路，严格上说，到达每个位置的最优消费应该是最好的（优惠券 + 到达成本）
 * 但是因为实际上的花费来源有绝对的“势能”存在，所以不可能冲突：
 * - 一指更优的优惠券重复使用：只要出现一次，第二张就已经被用掉了，直接免费
 * - 二指不会存在优惠券次优但是成本更低：增加了的势能一定被前面的优惠券抵消了
 * - 就像在排序后的斜坡上放倒三角一样，一旦放了就整体拉平了一段的价格
 * 个人还是建议画成排序之后的样子，然后放倒三角更好理解一些（
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

const int N = 1e5 + 5;
int a[N], c[N], id[N];

bool compare(int l, int r)
{return a[l] < a[r];}

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    longs ans = 0;
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt(),
        c[i] = scanner.nextInt(),
        ans += c[i];
    iota(id, id + 1 + n, 0);
    sort(id + 1, id + 1 + n, compare);
    longs discount = a[id[1]] + c[id[1]];
    for (int i = 2, p = id[i]; 
        i <= n; p = id[++ i])
    {
        ans += max(0ll, a[p] - discount);
        maximize(discount, (longs)a[p] + c[p]);
    }
    println(ans);
    return 0;
}