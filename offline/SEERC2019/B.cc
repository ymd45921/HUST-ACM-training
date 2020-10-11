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

#define eprintf(x...) fprintf(stderr, x...)
#define var(x) ""#x" = " << x 
#define lll __int128

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
    {x = read<T>(), (*this)(y...);}

    int nextInt() {return read<int>();}
    longs nextLongs() {return read<longs>();}  
    lll nextInt128() {return read<lll>();}    
} scanner;

const int N = 550;
const longs inf = 0x3f3f3f3f3f3f3f3f;
struct quest
{
    int x, t, y, r;
    bool operator<(quest &rhs)
    const {return x < rhs.x;}
} q[N];
longs dp[N][N], f[N][N];

int main()
{
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
#if 0
    freopen("in.txt", "r", stdin);
#endif
    int n, s1, s2, x, t, y, r;
    scanner(n, s1, s2);
    for (int i = 1; i <= n; ++ i)
    {
        scanner(x, t, y, r);
        q[i] = {x, t, y, r};
    }
    memset(dp, 0x3f, sizeof dp);
    sort(q + 1, q + 1 + n);
    dp[0][0] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        memcpy(f, dp, sizeof f);
        for (int j = s1; j >= 0; -- j)
            for (int k = s2; k >= 0; -- k)
                if (dp[j][k] != inf)
                {
                    if (j < s1)
                    {
                        int jj = j + q[i].x,
                            kk = k;
                        if (jj > s1)
                        {
                            kk = min(s2, jj - s1 + k);
                            jj = s1;
                        }
                        f[jj][kk] = min(f[jj][kk], dp[j][k] + q[i].t);
                    }
                    int kk = min(s2, k + q[i].y);
                    f[j][kk] = min(f[j][kk], dp[j][k] + q[i].r);
                }
        memcpy(dp, f, sizeof f);        
    }
    longs ans = dp[s1][s2];
    if (ans == inf || !ans) ans = - 1;
    printf("%lld\n", ans);

    return 0;
}

