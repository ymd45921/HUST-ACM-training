/**
 * 
 * 这是一个最大流问题，也可以用贪心模拟
 * 
 * 毕竟最大流也是某种意义上的贪心嘛
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

#define d(i) a[i][0]

using namespace std;
typedef long long longs;
typedef long double longd;
typedef unsigned long long ulong;

const char can[] = "possible";
const char cannot[] = "impossible";
const int N = 35;
const int M = 105;

int n,q,s;
int uq[M], c[N];
int d, a;
int tmp[N];
bool state = true;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    longs todo = 0;
    longs cando = 0;

    cin>>n>>q>>s;
    for(int i=1;i<=s;++i) cin>>uq[i];
    for(int i=1;i<=q;++i) cin>>c[i];
    for(int i=1;i<=n;++i)
    {
        cin>>d;                 // 本回合的资金
        for(int j=1;j<=s;++j) 
        {
            cin>>a;
            if(a > c[uq[j]]) state = false; // 不可能装下：直接暴毙
            tmp[uq[j]] += a;                
            if(tmp[uq[j]] > c[uq[j]])       // 用上回合的资金处理危险部分
            {
                cando -= tmp[uq[j]] - c[uq[j]];
                if(cando < 0) state = false;
                tmp[uq[j]] = c[uq[j]];
            }
            if(!state) break;
        }
        if(!state) break;
        cando += d;             // 使用本回合资金
        todo = 0;
        for(int i=1;i<=q;++i)
            todo += tmp[i];     
        if(todo <= cando)       // 可以全部处理完：清零
        {
            cando = todo = 0;
            memset(tmp,0,sizeof(int)*(q+1));
        }                       // 否则看下回合情况
    }
    if(todo > cando) state = false;

    if(state) cout<<can<<endl;
    else cout<<cannot<<endl;
    return 0;
}