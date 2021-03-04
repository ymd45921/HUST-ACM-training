/**
 *
 * 范围只有几百，一副 DP 的样子
 * 
 * 这区间 DP 写的还蛮离谱的（）
 * 还可以使用 KMP 和 Hash 预处理
 * 还有一种预处理公共串的神仙做法
 */
#include <bits/stdc++.h>

using namespace std;
using longs = long long;
using uint = unsigned;
using ulongs = unsigned long long;
using longd = long double;

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

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
    void operator()(char *x){scanf("%s", x);}
    void operator()(char &x){x = getchar();}

    template <class T, class... Ts>
    void operator()(T &x, Ts &... y)
    {(*this)(x), (*this)(y...);}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}
    char nextChar() {return getchar();}    
} scanner;

const int N = 777;
pair<int, int> seg[N][N];
int dp[N][N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n; char s[N];
    scanner(n, s);
    memset(seg, 0, sizeof seg);
    for (int l = 0; l < n; ++ l)
        for (int r = l + 1; r <= n; ++ r)
        {
            const int len = r - l;
            for (int i = r + 1; i <= n; ++ i)
                if (s[i - 1] != s[i - len - 1]) break;
                else if ((i - l) % len) continue;
                else 
                {
                    auto &ii = seg[l][i];
                    if ((!ii.second && !ii.first) || 
                        ii.second - ii.first > r - l)
                        ii.first = l, ii.second = r;
                }
        }    
    for (int len = 0; len <= n; ++ len)
        for (int l = 0, r = len; r <= n; ++ l, ++ r)
        {
            dp[l][r] = len;
            const auto &ii = seg[l][r];
            if (ii.first || ii.second)
                dp[l][r] = min(dp[l][r], dp[ii.first][ii.second]);
            for (int k = l; k <= r; ++ k)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r]);    
        }
    println(dp[0][n]);    

    return 0;
}

