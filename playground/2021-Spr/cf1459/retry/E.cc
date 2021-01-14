/**
 *
 * 上下左右操作姑且不论，先讨论什么是排序的逆运算：
 * - 定义上，一个排序 p 的逆运算的结果是 q，满足 p[q[i]] = i
 * 这种运算和矩阵初等变换并不能相结合，故不能直接维护；
 * - 如果仅有上下左右平移操作，只需要维护一个格子的平移情况即可
 * - 因为初始矩阵的每一个格子都会对应答案的一个格子
 * 所以，考虑可以维护转化关系，来维持行列级逆运算
 *
 * 参考平移行列的维护方法，那么逆运算可以进行这样的维护
 * - 对于序列 p 定义二元组 [i, x] 的含义是 p[i] = x
 * - 由逆运算的定义可得，逆运算结果 q 满足 p[q[i]] = i
 * - 即对于序列 p 有 [q[i], i]，而序列 q 是 [i, q[i]]
 * - 因此，求逆运算可以简单的通过交换二元组位置得到
 * 将上面这种处理方法扩展到排序矩阵的上下左右平移：
 * + 对于排序矩阵 a[i, j] = k, 定义三元组 [i, j, k]
 * + 那么上下左右平移对应的三元组变换就是 [i·1, j·1, k]
 * + 行级逆运算是 [i, k, j]，列级逆运算是 [k, j, i]
 * 因此，只需要维护三元组的变化情况，就可以计算出最终矩阵的结果
 *
 * 不得不说是很有意思的一个题目…… 学到了许多（
 * 而且实际上代码实现起来也没有那么容易==
 * 这一套题的质量是真的很不错，，
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

const int N = 1050, M = 1e5 + 5;
int a[N][N], ans[N][N];
char s[M];

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
        int n = scanner.nextInt(),
            m = scanner.nextInt();
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                a[i][j] = scanner.nextInt();
        scanner(s + 1);
        array<pair<char, int>, 3> trans
        {{{'i', 0}, {'j', 0}, {'k', 0}}};
        for (int i = 1; i <= m; ++ i)
            switch (s[i])
            {
                case 'U':
                    trans[0].second = (trans[0].second - 1 + n) % n;
                    break;
                case 'D':
                    trans[0].second = (trans[0].second + 1) % n;
                    break;
                case 'L':
                    trans[1].second = (trans[1].second - 1 + n) % n;
                    break;
                case 'R':
                    trans[1].second = (trans[1].second + 1) % n;
                    break;
                case 'I':
                    swap(trans[1], trans[2]);
                    break;
                case 'C':
                    swap(trans[0], trans[2]);
                    break;
                default: break;
            }
        const function apply = [&]
        (int i, int j, int k)
        {
            array<int, 3> neo{}, old{i, j, k};
            for (int ii = 0; ii < 3; ++ ii)
            {
                const auto &rule = trans[ii];
                neo[ii] = old[rule.first - 'i'] + rule.second;
                neo[ii] = (neo[ii] + n - 1) % n + 1;
            }
            ans[neo[0]][neo[1]] = neo[2];
        };
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                apply(i, j, a[i][j]);
        for (int i = 1; i <= n; ++ i)
            for (int j = 1; j <= n; ++ j)
                print(ans[i][j], " \n"[j == n]);
        if (T) println();
    }
    return 0;
}