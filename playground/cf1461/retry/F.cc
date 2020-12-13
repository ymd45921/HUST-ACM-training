/**
 *
 * 虽然但是，题目的情况应该不是很多：
 * - 任何情况下，减法都不能带来贡献；
 * - 只有两种符号且包含 - 时，总是使用另一种符号
 * - 其他的情况当作只有 + 和 * 时考虑
 * - 也就是有 1 的时候 + > *；有 0 的时候 + > *
 * - 其他的时候可进行转移 f[i] = f[j - 1] + Πa[j~i]
 * - 这个转移比较麻烦，是n²的，那么应该想办法优化
 * 优化后的代码执行流程如下：
 * + 首先，默认进行第一种转移方式；记录上一次用加号的位置为 i-1
 * + 如果这一位为 0，那么继续进行第二种转移是不优的，所以取消连续转移标志
 * + 如果为 1，采用默认 + 转移即可；否则尝试 * 转移
 * + 使用一个数组维护可以 * 转移的起点，已经它们后面的乘积
 * + 设定一个大数字 lim，当连续的值乘积大于 lim 时，总是进行 * 转移
 * + 将当前位置插入数组，作为可能的起点备用（？）
 * + 当已经出现大于 lim 的乘积的时候，就始终进行 * 转移
 * 这样，选取一个合适的 lim 值，就可以加快 DP 的第二位并保证答案正确
 * 
 * WA 9: 乘法 = 加法时，优先使用乘法——方便后面累加；不要随便从 2 开始！ 
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

const int N = 1e5 + 5;
int a[N], fw[N]; 
char opt[5], use[N];
longs f[N];

signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n = scanner.nextInt();
    for (int i = 1; i <= n; ++ i)
        a[i] = scanner.nextInt();
    scanner(opt);
    
    bool hasAdd = false, hasMul = false, hasMin = false;
    for (int cur = 0; opt[cur]; ++ cur) 
    switch(opt[cur])
    {
        case '+': hasAdd |= true; break;
        case '-': hasMin |= true; break;
        case '*': hasMul |= true; break;
        default: break;
    } 
    const auto oneOperator = [&](char op)
    {
        for (int i = 1; i < n; ++ i) print(a[i], op);
        println(a[n]), exit(EXIT_SUCCESS);
    };
    if ((hasAdd ^ hasMul ^ hasMin) && !(hasAdd & hasMul & hasMin))
        oneOperator(opt[0]);
    else if (!hasMul) oneOperator('+');
    else if (!hasAdd)
        for (int i = 2; i <= n; ++ i)
            if (!a[i]) use[i - 1] = '-';
            else use[i - 1] = '*';    
    else 
    {
        const int lim = 2 * n;
        vector<pair<int, longs>> q;
        bool overProduct = false;
        for (int i = 1; i <= n; ++ i)
        {
            f[i] = f[i - 1] + a[i], use[i - 1] = '+';
            fw[i] = i - 1;      // 默认进行第一种转移 (+)
            if (!a[i]) overProduct = false, q.clear();
            else if (a[i] > 1)  // 尝试进行第二种转移（*）
            {
                for (int j = 0, siz = q.size(); j < siz; ++ j)
                {
                    auto &[ind, prod] = q[j];
                    if (prod * a[i] >= lim)
                    {overProduct = true; break;}
                    else prod *= a[i];
                    if (f[ind] + prod >= f[i])
                        f[i] = f[ind] + prod, fw[i] = ind;
                }
                q.emplace_back(i - 1, a[i]);
                if (overProduct) fw[i] = q[0].first;
            }
        }
        const function<void(int)> parse = [&](int x)
        {
            if (!x) return; else parse(fw[x]);
            for (int i = fw[x] + 2; i <= x; ++ i) 
                use[i - 1] = '*';   
        }; parse(n);
    }
    for (int i = 1; i < n; ++ i) print(a[i], use[i]);
    print(a[n], '\n');
    return 0;
}