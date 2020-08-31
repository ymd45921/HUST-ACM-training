/**
 *
 * 哈哈，想不到吧
 * 这题贪心会贪死的
 *
 * 我操，标程超时
 */
#include <iostream>
#include <cstring>
#include <algorithm>

#define cline(x) memset(x,0x3f,sizeof(longs)*(m1))

using namespace std;
typedef long long longs;

const int N = 405;
const longs INF = 0x3f3f3f3f3f3f3f3f;

longs f[N<<2][N];
int wide[N<<2];
int n,m,li,m1;
int a[N];
int sum = 0;

void update(int line)
{
    cline(f[line]);
    const int l = line<<1;
    const int r = l^1;
    int p;
    for(int i = wide[l]; i <= m; ++ i)
        for(int j = wide[r]; (p = i+j) <= m; ++ j)
            f[line][p] = min(f[line][p], f[l][i]+f[r][j]);
}

void calculate(int num, int index)
{
    cline(f[index]);
    const int lim = min(li,a[num]);
    for(int i = 1; i <= lim; ++i)
    {
        const longs val = a[num] / i;
        const longs mod = a[num] % i;
        f[index][i] = mod*(val+1)*(val+1) + (i-mod)*val*val;
    }
}

void build(int l, int r, int index)
{
    wide[index] = r - l + 1;
    if(l==r)
    {
        calculate(l,index);
        return;
    }
    int m = l+r>>1;
    build(l, m, index << 1);
    build(m+1, r, index << 1 ^ 1);
    update(index);
}

void modify(int l, int r, int index, int x)
{
    if(l==r)
    {
        calculate(l,index);
        return;
    }
    int m = l+r>>1;
    if(x <= m) modify(l, m, index << 1, x);
    else modify(m+1, r, index << 1 ^ 1, x);
    update(index);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>m;
    li = m-n+1;
    m1 = m+1;
    for(int i = 1; i <= n; ++ i)
    {
        cin>>a[i];
        f[i][1] = a[i]*a[i];
        sum += a[i];
    }
    build(1,n,1);

    int q,x,v;
    cin>>q;
    while(q--)
    {
        cin>>x>>v;
        sum += v-a[x];
        a[x] = v;
        modify(1,n,1,x);
        cout<<f[1][min(m,sum)]<<endl;   // 总数不超过x的石头不会被分为超过x堆
    }

    return 0;
}