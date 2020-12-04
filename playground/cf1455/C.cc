/**
 *
 * 游戏规则：
 * - 击球消耗次数；如果是发球回合，发球方有体力的话必须击球
 * - 如果是回球回合，回球方可以选择放弃回球输掉比赛
 * - 双方希望可以最大化自己的获胜次数，然后削减对手的获胜次数
 * - 玩家一号先发球
 *
 * 虽然这个情况并不是十分复杂，但是还可以简化为对称条件：发球方也可以选择
 * 转化为对称条件的话，这个问题的表示就是可递推可转移的了。
 * 这样的话，显然有 win(0, y) = (0, y) 和 win(x, 0) = (0, x)
 * 转移的过程可以表示为：win(x, y) => ^win(y, x - 1)，记作 ~win
 * 后手玩家可以决定是否接球，所以转移有两种情况：打球消耗体力或者认输
 * + 打回去：~win = ^win(y, x - 1)
 * + 认输：~win = ^[win(y, x - 1) + (0, 1)]
 * 使用数学归纳法证明 win(x, y) = (x, y)；win 函数会倾向选择认输以达成更多次数
 * 再加上本题的限制条件，win'(x, y) => ^win(y, x - 1)
 *
 * 此题不难，做不出来，唯手生耳（
 * 你不是老会找规律了🐎，这么明显的 (x - 1, y) 的规律你没看出来？
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
void print(char *s) {printf(s);}
void print(char ch) {putchar(ch);}
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

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt(), x, y;
    while (t --)
    {
        scanner(x, y);
        printf("%d %d\n", x - 1, y);
    }
    return 0;
}