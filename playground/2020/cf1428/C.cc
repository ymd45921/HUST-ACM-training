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

#define eprintf(x...) fprintf(stderr, x)
#define var(x) ""#x" = " << x
#define lll __int128
#define minimize(a, b) (a = min(a, b))
#define maximize(a, b) (a = max(a, b))

template <class T>
void println(const T x)
{puts(to_string(x).c_str());}
void println(const char *s){puts(s);}
void println(const char ch)
{putchar(ch), putchar('\n');}

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

public:

    template <class T>
    void operator()(T &x){x = read<T>();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}
} scanner;
#define isA(i) (s[i] == 'A')

const int N = 2e5 + 5;
int dp[N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif

    int t, n, l; string s;
    cin >> t;
    while (t --)
    {
        cin >> s;
        n = s.length();
        int cntA = 0, cntB = 0;
        for (int i = 0; i < n; ++ i)
            ++ (isA(i) ? cntA : cntB);
        dp[0] = isA(0);
        for (int i = 1; i < n; ++ i)
            dp[i] = max(0, dp[i - 1] + (isA(i) ? 1 : -1));
        dp[n] = dp[n - 1];
        auto use = cntA - dp[n], lastB = cntB - use;
        auto ans = dp[n] + (lastB % 2);
        println(ans);
    }

    return 0;
}

