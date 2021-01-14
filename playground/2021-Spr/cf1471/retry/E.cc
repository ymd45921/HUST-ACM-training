/**
 *
 * 确实，距离 p 相等距离的两个人的卡牌数量和是 2k：
 * - 使用数学归纳法证明该结论；在初始状态 a，这个命题显然成立；
 * - 假设距离 p 距离相等的两个位置 i 和 j 分别在左侧右侧，距离 p 为 s
 * - 设变化之后的状态为 b，有定义：b[i] = floor(a[i+1] / 2) + ceil(a[i-1] / 2)
 * - 交换律、结合律：b[i] + b[j] = (f(a[j+1] / 2) + c(a[i-1] / 2)) + ...
 * - 对于 a + b = 2k，显然有 floor(a / 2) + ceil(b / 2) = k
 * - 那么两个部分都可以识别为距离 p 为 s-1 和 s+1 的两组人的手牌总数的一半，为 k
 * 故 b 也满足命题，证明完毕。
 *
 * 由上述结论可以推导出，p 号玩家一直拥有 k 张手牌；
 * 再继续证明：从 p 玩家出发，向右遍历直到回到 p 前，玩家手牌数是不递增的
 * - 算了看不懂，就定性的说明一下：首先，随便手玩几步，这个条件肯定是成立的
 * - 对于 b[i+1] 和 b[i]，分别写出基于上一个状态 a 的递推式，可见这个条件是传递的
 * 因此，可以定性的证明从 p 向右出发，直到回到 p 之前，玩家的手牌数量是不递增的
 * 综上两组结论，前 n / 2 步，≠k 的人数逐渐增加，这是显然的。
 *
 * 因此，我们可以做出如下的交互策略：
 * + 首先，先等待 √n 次操作：这样可以使得 n 个人中分别有 √n 个 ≠k
 * + 找到一个大于 k 的位置，作为右端点并进行适当的平移
 * + 在进行了偏移之后的区间上进行非常规的二分查找，查找 gap 的位置
 * 根据前面推导的结论，gap 的位置就是玩家 p 的位置
 *
 * 此外，随着模拟的进行，大的数字会更大，小的数字会更小，单调性未被破坏
 * 在 p 的右边的值是严格大于等于 bound 的，而左边是小于等于的
 *
 * 这，，还真是距离独立做出这个题差得远了（
 * 这种成环的题还真的有点麻烦，得想点办法写的更加稳健
 * WA3: 怎么在二分条件上加了个等号救过了？
 * 推测：影响这一点的因素，大的在变大，小的在变小之外，是否存在两个不为 k 的值相等？
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

#define ask(x) cout << "? " << (x) + 1 << endl, cin
#define check(x) cout << "! " << (x) + 1 << endl
#define turn(x) ((off + (x)) % n)

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, k, x, cur;
    cin >> n >> k;
    int root = sqrt(n);
    for (int i = 1; i <= root; ++ i) ask(0) >> x;
    x = 0, cur = 0;
    const function boundary = [&]
    {
        while (x <= k && cur < n)
        {
            ask(cur) >> x;
            if (x > k) break;
            else cur += root - 1;
        }
    }; boundary();
    int d = n - 1 - cur, off = n - d;
    assert(turn(n - 1) == cur);
    int l = 0, r = n - 1, b = x;
    while (l < r)
    {
        int mid = (l + r) / 2;
        int id = turn(mid);
        ask(id) >> x;
        if (x >= b) b = x, r = mid; // ?? 加了个等号就过了 ??
        else l = mid + 1;
    }
    check(turn((r + n - 1) % n));
    return 0;
}