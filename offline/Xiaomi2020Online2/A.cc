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

const int N = 1e5 + 5;
const int inf = 0x3f3f3f3f;
int dp[N][5];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n; string s;
    while (cin >> n >> s)
    {
        dp[0][1] = dp[0][2] = dp[0][3] = dp[0][4] = 0;
        dp[0][0] = 1;
        //if (s[0] == '2') dp[0][1] = 0;
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 0; j <= 4; ++ j)
                dp[i][j] = dp[i - 1][j];
            if (s[i-1] == '1') continue;    
            if (s[i-1] == '2') 
            {
                // maximize(dp[i][1], dp[i - 1][0]);
                // maximize(dp[i][3], dp[i - 1][2]);
                dp[i][1] += dp[i-1][0];
                dp[i][3] += dp[i-1][2];
            }   
            else
            {
                // maximize(dp[i][2], dp[i - 1][1]);
                // maximize(dp[i][0], dp[i - 1][3] + 1);
                dp[i][2] += dp[i-1][1];
                dp[i][4] += dp[i-1][3];
            }
        }
        int ans = dp[n][4];
        // for (int i = 0; i < 4; ++ i)
        //     maximize(ans, dp[n - 1][i]);
        cout << ans << endl;    
    }
    return 0;
}

