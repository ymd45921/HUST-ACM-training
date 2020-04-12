#include <bits/stdc++.h>
#define ll long long
using namespace std;


const int maxn = 2e3 + 10;
int n, m;
int tcase;
int a[maxn][maxn];
int l[maxn][maxn], r[maxn][maxn], u[maxn][maxn];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> tcase;
    int ans, anss;
    while(tcase--)
    {
        cin >> n >> m;
        char ch;
        ans = 0;
        anss = 0;
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= m; j++)
            {
                cin >> ch;
                a[i][j] = ch - 'A';
                l[i][j] = r[i][j] = j;
                u[i][j] = 1;
            }
        }
        for(int i = 1; i <= n; i++)
        {
            for(int j = 2; j <= m; j++)
            {
                if(a[i][j] == a[i][j-1])
                {
                    l[i][j] = l[i][j-1];
                }
            }
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=m-1;j>=1;j--)
            {
                if(a[i][j]==a[i][j+1])
                {
                    r[i][j]=r[i][j+1];//向右
                }
            }
        }

        for(int i=2;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                if(a[i][j]==a[i-1][j])
                {
                    l[i][j]=max(l[i][j],l[i-1][j]);
                    r[i][j]=min(r[i][j],r[i-1][j]);
                    u[i][j]=u[i-1][j]+1;//向上
                }
                int x=r[i][j]-l[i][j]+1;
                int y=u[i][j];
                ans = max(ans, min(x, y));
            }
        }
        cout << ans << endl;
    }

    return 0;
}
