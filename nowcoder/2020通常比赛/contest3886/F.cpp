/**
 * 
 * 暴力倒是叫人理解，康托展开我已经忘了
 * 
 * 康托展开可以判断全排列的位数
 * 
 * 着康托展开还能线段树哈希表优化，可以压缩
 * 有点牛逼
 * 
 * P3014
 */
#include <iostream>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;
typedef long long longs;

int out[25];
int read[25];
longs fact[25];

// inline int lambda(set<int> &s, int x)
// {
//     auto it = s.begin();
//     for(int i=0;i<=x;++i) ++it;
//     return *it;
// }

inline void preProcess()
{
    // for(int i=0;i<n;++i)
    //     cows[i] = i+1;
    // nowpermt = 1;
    fact[0] = fact[1] = 1;
    for(int i=2;i<=20;++i)
    fact[i] = fact[i-1]*i;
}

inline longs cantorExpanse(int n)
{
    longs ans = 1;
    for(int i=0,m=n-1;i<n;++i,--m)
    {
        int cnt = 0;
        for(int j=i+1;j<n;++j)
            if(read[i]>read[j]) ++cnt;
        ans += fact[m]*cnt;
    }
    return ans;
}

inline void cantorInverse(int n, longs x)
{
    longs now = x-1;
    int modc;
    // set<int> s;
    // for(int i=1;i<=n;++i) s.insert(i);
    bool v[21]{0};
    for(int i=0,m=n-1;i<n;++i,--m)
    {
        modc = now/fact[m];
        for(int j=1;j<=n;++j)
            if(!v[j]) if(modc--==0) 
            {
                out[i] = j;
                v[j] = true;
                break;
            }
        now %= fact[m];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    preProcess();
    int n,k,x; char cmd;
    while(cin>>n>>k)
    {
        for(int i=0;i<k;++i)
        {
            cin>>cmd;
            if(cmd=='P')
            {
                cin>>x;
                cantorInverse(n,x);
                for(int j=0;j<n;++j)
                    cout<<out[j]<<' ';
                cout<<endl;
            }
            else
            {
                for(int j=0;j<n;++j)
                    cin>>read[j];
                cout<<cantorExpanse(n)<<endl;
            }       
        }
    }

    return 0;
}