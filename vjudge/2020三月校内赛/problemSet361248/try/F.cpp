/**
 *
 * 确实一眼二分，但是怎么模拟来确信这个呢？
 *
 * 忽略所有的重量低于M的（反正也没有贡献
 * 检查接下来的是否合理
 *
 * 那个sweep的写法也挺有趣的
 *
 * WA: check函数崩了
 */
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

const int N = 1e6+5;

int n;
int in[2][N];

bool check(int m)
{
    int last;
    bool got = false;
    for(int i=0;i<n;++i)
    {
        if(in[0][i]<=m) continue;
        if(!got)
        {
            got = true;
            last = in[0][i];
        }
        else
        {
            if(last!=in[0][i])
                return false;
            got = false;
        }
    }
    if(got) return false;
    for(int i=0;i<n;++i)
    {
        if(in[1][i]<=m) continue;// 上点心吧
        if(!got)
        {
            got = true;
            last = in[1][i];
        }
        else
        {
            if(last!=in[1][i])
                return false;
            got = false;
        }
    }
    return !got;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen(R"(D:\shiroha\Downloads\nwerc2016testdata.tar\nwerc2016testdata\free_weights\6-lightly-shuffled.in)","r",stdin);

    cin>>n;
    int max = 0, min = 0x7fffffff;
    for(int i=0;i<n;++i)
    {
        cin>>in[0][i];
        if(in[0][i]>max) max = in[0][i];
        if(in[0][i]<min) min = in[0][i];
    }
    for(int i=0;i<n;++i)
    {
        cin>>in[1][i];
        if(in[1][i]>max) max = in[1][i];
        if(in[1][i]<min) min = in[1][i];
    }

    longs l = 0;
    longs r = max;
    while(l<=r)
    {
        const longs mid = (l+r)>>1;
        if(check(mid)) r = mid-1;
        else l = mid+1;
    }
    cerr<<"check(9589) = "<<check(9589)<<endl;
    cout<<l<<endl;

    return 0;
}