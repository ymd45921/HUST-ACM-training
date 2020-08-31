/**
 * 用cstring还不如用
 * 
 * 
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;
typedef long long longs;

const int N = 45;

int n,m;

string in[N];
string dp[N][100];
bool vis[N][100];
string ans[N];
string tmp;
int mem[N][100];

bool make(string&now, string&Next, int m, int k)
{
    int num = k; int pos;
    tmp = Next;
    if(!k) return tmp >= now;
    for(pos=0;pos<m&&num>0;++pos)
    {
        if(tmp[pos]!=now[pos])
        {
            tmp[pos] = now[pos];
            --num;
        }
    }
    if(tmp>=now) return true;

    for(--pos;pos>=0&&now[pos]=='9';) --pos;
    if(pos<0) return false;
    num = k;
    tmp = Next;
    for(int i=0;i<pos;++i)
    {
        if(tmp[i]!=now[i])
        {
            tmp[i] = now[i];
            --num;
        }
    }
    if(tmp[pos]!=now[pos]+1)
    {
        tmp[pos] = now[pos] + 1;
        --num;
    }
    for(++pos; pos < m && num > 0; ++pos)
    {
        if(tmp[pos]!='0')
        {
            tmp[pos] = '0';
            --num;
        }
    }
    return true;
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;

    for(int i=1;i<=n;++i) cin>>in[i];

    dp[0][0] = string(m,'0');
    const int most = n<<1;
    memset(vis,true,sizeof(vis));

    for(int i=1;i<=n;++i)
    {
        for(int j=0;j<=most;++j)
        {
            if(vis[i][j]) continue;
            for(int k=0;k<=m&&j+k<most;++k)
            {
                if(make(dp[i][j], in[i+1], m, k) &&
                    vis[i+1][j+k] || tmp < dp[i+1][j+k]
                )
                {
                    vis[i+1][j+k] = false;
                    dp[i+1][j+k] = tmp;
                    mem[i+1][j+k] = j;
                }
            }
        }
    }

    int ptr = 0;
    for(;ptr<most;++ptr)
    {
        if(!vis[n][ptr]) break;
    }
    for(int i=n;i>0;ptr=mem[i][ptr],--i)
    {
        ans[i] = dp[i][ptr];
    }
    for(int i=1;i<=n;++i)
    {
        cout<<ans[i]<<endl;
    }

    return 0;
}