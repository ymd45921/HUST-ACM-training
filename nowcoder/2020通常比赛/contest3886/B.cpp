/**
 *
 * 双重二分找答案？
 * 双重二分果然还是太麻烦了，直接二分就好了
 * 毕竟累计判定时间并不算是犯法的事情
 *
 * 但是总的而言这是一道不错的二分
 *
 * USACO2011 - P3017
 */
#include <iostream>

using namespace std;
typedef long long longs;

const int N = 505;

int map[N][N]{0};
int sum[N][N]{0};
int r,c,a,b;

inline int mat(int x,int y,int a,int b)
{
    return sum[a][b]+sum[x][y]-sum[x][b]-sum[a][y];
}

bool check(int x)
{
    int ptr = 0, cur = 0;
    for(int i=1;i<=r;++i)
    {
        int now = 0, cnt = 0;
        for(int j=1;j<=c;++j)
        {
            now += mat(i,j,ptr,j-1);
            if(now >= x)
                now = 0, ++cnt;
        }
        if(cnt >= b) ptr = i, ++cur;    // 否则再加一行
    }
    return cur >= a;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>r>>c>>a>>b;
    for(int i=1;i<=r;++i)
        for(int j=1;j<=c;++j)
        {
            cin>>map[i][j];
            map[0][j] += map[i][j];
            map[i][0] += map[i][j];
            sum[i][j] = sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1]+map[i][j];
        }
    int L = 0, R = sum[r][c];
    int ans = 0;
    while (L<=R)
    {
        int mid = L+R>>1;
        if(check(mid))
            L = mid+1, ans = mid;
        else R = mid-1;
    }
    cout<<ans<<endl;

    return 0;
}