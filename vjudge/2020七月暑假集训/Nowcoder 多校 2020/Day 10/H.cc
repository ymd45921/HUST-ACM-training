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

const int N = 330;
bitset<N> use[N], gra[N];
short map[N][N];

bool check(int i, int j)
{
    return map[i + 1][j] > 1 && map[i - 1][j] > 1
        && map[i][j + 1] > 1 && map[i][j - 1] > 1;
}

void place(int i, int j)
{
    -- map[i + 1][j], -- map[i - 1][j];
    -- map[i][j + 1], -- map[i][j - 1];
    use[i + 1][j] = use[i - 1][j] = true,
    use[i][j + 1] = use[i][j - 1] = true;
    gra[i][j] = use[i][j] = true;
}

void solution(int n)
{
    auto n1 = n + 1;
    for (int i = 0; i <= n1; ++ i)
        for (int j = 0; j <= n1; ++ j)
            map[i][j] = 4;
    for (int i = 1; i <= n; ++ i)
        -- map[i][1], -- map[i][n],
        -- map[1][i], -- map[n][i];
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            if (!use[i][j] && check(i, j)) place(i, j);
}

int main()
{
    ios::sync_with_stdio(false);

    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), n1 = n + 1;
        if (n == 1) {puts("1"); continue;}
        solution(n);
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= n; ++ j)
                printf("%d", gra[i][j] ? 1 : 0);
            puts("");
        }
        for (int i = 0; i <= n1; ++ i)
        {
            use[i].reset(), gra[i].reset();
            memset(map[i], 0, sizeof(short)*(n1 + 1));
        }
    }

    return 0;
}