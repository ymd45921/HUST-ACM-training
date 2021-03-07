/**
 *
 * 怎么做这个题目？有两个需要注意的地方
 * - 鸽巢定理：最多出现的次数 x <= (n + 1) / 2，则可以相邻不同
 * - 线性时间求出合并后的序列，并且求出其众数
 * - 结合上述两点：线性时间求出合并后的序列是否包含次数超过一半的数字
 * 求出序列中是否包含出现次数超过一半的数，可以使用摩尔投票法
 * 当然，还有一种是使用位运算：求出每一位的众数，可以合并成超过一般的数字
 *
 * 数据只有 1e6，我觉得不线性时间卡卡也能过去吧（
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
    template<class name>
    fast_read operator, (name &x)
    {scanner(x); return fast_read{};}
} fastRead;
#define $$ fastRead,

const int N = 1e6 + 5;

struct op
{
    int type = 0, dep[2] = {};
    vector<int> arr;
} ops[N];
longs t[N];

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
        int n = scanner.nextInt(), x;
        for (int i = 1; i <= n; ++ i)
            if ((ops[i].type = scanner.nextInt()) == 1)
            {
                ops[i].arr.clear();
                int k = scanner.nextInt();
                while (k --) {$$ x; ops[i].arr.push_back(x);}
            } else $$ ops[i].dep[0], ops[i].dep[1];
        memset(t, 0, sizeof(longs) * (n + 1));
        t[n] = 1;
        for (int i = n; i > 0; -- i)
            if (ops[i].type == 2)
                for (auto ii : ops[i].dep)
                    t[ii] += t[i];
        longs num = 0, weigh = 0, sum = 0;  // 摩尔投票法
        for (int i = 1; i <= n; ++ i)
            if (t[i] && ops[i].type == 1)
            {
                for (auto ii : ops[i].arr)
                    if (!num) num = ii, weigh += t[i];
                    else if (ii == num) weigh += t[i];
                    else
                    {
                        weigh -= t[i];
                        if (weigh < 0)
                            num = ii, weigh = -weigh;
                    }
                sum += ops[i].arr.size() * t[i];
            }
        longs cnt = 0;
        for (int i = 1; i <= n; ++ i)
            if (t[i] && ops[i].type == 1)
                for (auto ii : ops[i].arr)
                    if (ii == num) cnt += t[i];
        println(min((sum - cnt) * 2, sum));
    }
    return 0;
}