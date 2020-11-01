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

    static inline bool isSeparator(int x)
    {return x == ' ' || x == '\n';}
public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){do x = getchar(); while (isSeparator(x));}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar()
    {int x = getchar(); while (isSeparator(x)) x = getchar(); return x;}
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

const int N = 1e5;

longs fastPow(longs a, uint b)
{
    longs ans = 1;
    while (b)
    {
        if (b & 1u) ans = (ans * a);
        a = (a * a);
        b >>= 1u;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int t = scanner.nextInt();
    auto prime = EulerSieve<N>();
    while (t --)
    {
        longs p, q;
        scanner(p, q);
        if (p % q) println(p);
        else
        {
            auto res = p / q;
            unordered_map<int, int> part;
            auto tmp = q;
            for (auto ii : prime)
            {
                while (tmp % ii == 0)
                    ++ part[ii], tmp /= ii;
                if (tmp == 1) break;
            }
            if (tmp != 1) ++ part[tmp];
            longs ans = 0;
            for (auto [num, tim] : part)
            {
                tmp = p;
                while (tmp % num == 0) tmp /= num;
                maximize(ans, tmp * fastPow(num, tim - 1));
            }
            println(ans);
        }
    }

    return 0;
}

