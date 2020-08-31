#include <bits/stdc++.h>

using namespace std;
const int N = 45, M = 405;
const int N2 = N<<1;

int n, m;
char in[N][M];
char tmp[M];            // findNext的返回值
char dp[N][N2][M];
bool flag[N][N2];
int pre[N][N2];
char* ans[N];

bool findNext(char *now, char *Next, int m, int k)
{
    int num = k, pos;
    strcpy(tmp, Next);
    if(!k)
        return strcmp(tmp, now) >= 0;
    for(pos = 0; pos < m && num > 0; ++pos)
        if(tmp[pos] != now[pos])
        {
            tmp[pos] = now[pos];
            --num;
        }
    if(strcmp(tmp, now) >= 0)
        return true;

    for(--pos; pos >= 0 && now[pos] == '9'; )
        --pos;
    if(pos < 0)
        return false;
    num = k;
    strcpy(tmp, Next);

    for(int i = 0; i < pos; ++i)
    {
        if(tmp[i] != now[i])
        {
            tmp[i] = now[i];
            --num;
        }
    }

    if(tmp[pos] != now[pos] + 1)
    {
        tmp[pos] = now[pos] + 1;
        --num;
    }

    for(++pos; pos < m && num > 0; ++pos)
    {
        if(tmp[pos] != '0')
        {
            tmp[pos] = '0';
            --num;
        }
    }
    return true;
}

inline void init()
{
    memset(flag, false, sizeof(flag));
    for(int i = 0; i < m; ++i)
        dp[0][0][i] = '0';
    dp[0][0][m] = '\0';
    flag[0][0] = true;
}

int main()
{
    scanf("%d%d%*c", &n, &m);
    const int n2 = n << 1;

    for(int i = 1; i <= n; ++i)
        scanf("%s", in[i]);
    init();

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n2; ++j)
    {
        if(!flag[i][j]) continue;
        for(int k = 0; k <= m && j + k < n2; ++k)
        {
            if(findNext(dp[i][j], in[i + 1], m, k)
                && ( !flag[i + 1][j + k]
                || strcmp(tmp, dp[i + 1][j + k]) < 0
            ))
            {
                flag[i + 1][j + k] = true;
                strcpy(dp[i+1][j+k], tmp);
                pre[i+1][j+k] = j;
            }
        }
    }

    int ptr;
    for(ptr = 0; ptr < n2; ++ptr)
        if(flag[n][ptr]) break;
    for(int i = n; i > 0; ptr = pre[i][ptr], --i)
        ans[i] = dp[i][ptr];
    for(int i = 1; i <= n; ++i)
        puts(ans[i]);
    return 0;
}