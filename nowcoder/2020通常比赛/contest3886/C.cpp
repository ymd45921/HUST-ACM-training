/**
 * 
 * P3016 这竟然就算是比较裸的模拟？
 * 
 * 2k以上确实是不必要的。
 * 强硬的模拟
 */
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;

const int N = 705;

struct pos{int x,y;};

int tag[N][N];
longs sum[N][N]{0};
int n,k;

// longs triangle(pos p, bool dir, int k)
// {
//     longs ans = 0;
//     int cx = p.x, cy = p.y;
//     if(dir)
//     {
//         const int bd = p.y-1;
//         for(int i=1;i<=k;++i,++cx,++cy)
//             ans += (longs)sum[cx][cy]-sum[cx][bd];
//     }
//     else
//     {
//         --cy;
//         for(int i=1;i<=k;++i,--cx,--cy)
//             ans += (longs)sum[cx][p.y]-sum[cx][cy];
//     }
//     return ans;
// }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=i;++j)
        {
            cin>>tag[i][j];
            sum[i][j]=sum[i][j-1]+tag[i][j];
        }

    const int k2 = k<<1;
    longs now, cnt, ans = -0x7fffffffffffffff;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=i;++j)
        {
            now = cnt = 0ll;
            const int bd1 = j-1;
            for(int x=1;x<=k2;++x)
            {
                const int px = x+i-1;
                if(px>n) break;
                now += sum[px][x+j-1]-sum[px][bd1];
                cnt += x;
                if(x>=k) ans = max(ans,now/cnt);
            }
            now = cnt = 0ll;
            for(int x=1;x<=k2;++x)
            {
                const int px = 1+i-x;
                const int py = j-x+1;
                if(px<1||py<1||j>px) break;
                now += sum[px][j]-sum[px][py-1];
                cnt += x;
                if(x>=k) ans = max(ans,now/cnt);
            }
        }
    cout<<ans<<endl;

    return 0;
}