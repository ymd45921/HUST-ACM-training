/**
 *
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 550, NN = N * N;

bitset<N> map[N];
int sum[N][N];
int tot[NN * 2], s[NN];

int main()
{
    ios::sync_with_stdio(false);

    int n = nextInt(), m = nextInt();
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= m; ++ j)
            map[i][j] = (bool) nextInt(),
            sum[i][j] = sum[i - 1][j] + (map[i][j] ? 1 : -1);
    longs ans = 0; s[0] = NN;
    for (int i = 1; i <= n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
        {
            int pre = 1;
            for (int k = 1; k <= m; ++ k)
            {
                if (map[i][k] || map[j][k])
                {
                    for (int l = pre; l <= k; ++ l)
                        if (sum[j][l] - sum[i - 1][l] == j - i + 1)
                            -- tot[s[l]];
                    pre = k + 1, s[k] = NN;    
                }
                if (sum[j][k] - sum[i - 1][k] == j - i + 1)
                    ans += tot[s[k - 1]] + tot[s[k - 1] + 1] + tot[s[k - 1] - 1];
                
            }
            
        }


    return 0;
}