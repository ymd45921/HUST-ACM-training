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

#define lll __int128
#define minimize(a, b) ((a) = min(a, b))
#define maximize(a, b) ((a) = max(a, b))
#define sgn(x) ((x) < 0 ? -1 : (x) > 0)
#define puti(n) puts(to_string(n).c_str())

#if 1
#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define watch(args...) cerr << args << endl
#define $$ << ", " <<
#define vars(x, y...) var(x) << ", " << vars(y)
#else
#define eprintf(...)
#define watch(...)
#endif

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

const int N = 2e5 + 5;

namespace StringHasher
{
    const int base = 6151;
    const int offset = 97;
    ulongs pow[N], var1[N], var2[N];

    auto idx = [](const char ch){return ch + 1;};

    template <class T>
    void calculate(const T* s, ulongs *var, int n)
    {
        var[0] = idx(s[0]) + offset;
        for (int i = 1; i < n; ++ i)
            var[i] = var[i - 1] * base + idx(s[i]) + offset;
    }

    void init(int len = N)
    {
        pow[0] = 1;
        for (int i = 1; i < len; ++ i)
            pow[i] = pow[i - 1] * base;
    }

    ulongs getHashCode1(int l, int r)
    {
        if (l == r || !r) return 0ull;
        auto etc = l ? var1[l - 1] : 0ull;
        return var1[r - 1] - etc * pow[r - l];
    }

    ulongs getHashCode2(int l, int r)
    {
        if (l == r || !r) return 0ull;
        auto etc = l ? var2[l - 1] : 0ull;
        return var2[r - 1] - etc * pow[r - l];
    }
}

int s[N], r[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n;
    StringHasher::init();
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++ i)
            cin >> s[i], s[i + n] = s[i];
        int n2 = n * 2, n21 = n2 + 1;
        for (int i = 1; i < n2; ++ i)
            r[i] = s[n21 - i];
        StringHasher::calculate(s, StringHasher::var1, n21);
        StringHasher::calculate(r, StringHasher::var2, n21);
        unordered_set<ulongs> table;
        for (int i = 1; i <= n; ++ i)
            table.insert(StringHasher::getHashCode1(i, i + n)),
            table.insert(StringHasher::getHashCode2(i, i + n));
        auto ans = table.size();
        cout << ans << endl;    
    }

    return 0;
}

