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

#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(...) trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define eprintf(...)
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

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = (char)getchar(); while (isBlank(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {char x; (*this)(x); return x;}
} scanner;


template <int n> vector<int> &EulerSieve()
{
    static vector<int> prime;
    bitset<n> vis;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime.push_back(i);
        for (auto & pp : prime)
        {
            if ((longs)i * pp > n) break;
            vis[i * pp] = true;
            if (i % pp == 0) break;
        }
    }
    return prime;
}

const int maxn = 3e4 + 10;
vector<double> v[maxn];
vector<int> c[maxn];
double f[maxn];
double ans[maxn];
void init(int n)
{
    for(int i = 1; i <= n; i++)
    {
        f[i] = 0;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("out.txt", "w", stdout);
#endif
    const int N = 3e4 + 10;
    int t = scanner.nextInt();
    auto &p = EulerSieve<N>();
    int cnt = 1;
    for(auto ii:p)
    {
        int tmp = 1;
        while(true)
        {
            tmp *= ii;
            if(tmp > 30000) break;
            v[cnt].push_back(log(tmp));
            c[cnt].push_back(tmp);
        }
        if(ii > 30000)
        {
            break;
        }
        cnt++;
    }
    int b = 30000;
    init(b);
    for(int i = 1; i < cnt; i++)
    {
        if(c[i][0] > b) break;
        for(int j = b; j >= 0; j--)
        {
            for(int k = 0; k < v[i].size() && j - c[i][k] >= 0; k++)
            {
                f[j] = max(f[j], f[j - c[i][k]] + v[i][k]);
            }
        }
    }

    while (t --)
    {
        scanner(b);
        printf("%.9f\n", f[b]);
    }
    return 0;
}