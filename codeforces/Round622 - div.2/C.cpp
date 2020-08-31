/**
 *
 * 脑海中浮现了差分，找到所有极大值再进行暴力求解
 * 虽然极值应该蛮快的，但是数据坑你的话这就没了==
 *
 * 比起简单版本，这里可以优化，也可以有别的做法。
 *
 * 就说单调栈的做法好了吧：
 * 单调栈的作用：找到i左侧第一个小于和右侧第一个不大于
 * 左边的就是f[i]=m[i]*(i-k-1)+f[k]，k是第一个小于
 *
 * 日，果然还是不需要两次单调栈找lr的嘛
 * 这个左小于右不大于完全没有什么问题==
 * 出问题都是因为很多的小细节的地方写错了
 *
 * 害==怎么害WA了（）
 * i,j不分，啪，你死了==
 * 一longs到底别忘记了
 *
 * 这个题目还有一种常用做法就是：线段树+分治
 */
#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;
typedef long long longs;

const int N = 5e5+50;
longs n,m[N];               // m[]涉及到乘法，必须longs
longs ans[N];               // 为了用min也要longs
int l[N],r[N];
longs fl[N],fr[N];
stack<int> s;

inline void pop(int i)
{
    r[s.top()] = i;
    s.pop();
}

inline void push(int i)
{
    while(!s.empty()&&m[s.top()]>m[i]) pop(i);
    if(s.empty()) l[i] = 0;
    else l[i] = s.top();
    s.push(i);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    const int npos = n+1;
    fl[0] = fl[npos] = 0;
    fr[0] = fr[npos] = 0;
    m[0] = m[npos] = 0;

    for(int i=1;i<=n;++i)
    {
        cin>>m[i];
        push(i);
    }
    while(!s.empty()) pop(npos);

    for(int i=1,j=n;i<=n;++i,--j)
    {
        fl[i] = fl[l[i]]+m[i]*(i-l[i]-1)+m[l[i]];
        fr[j] = fr[r[j]]+m[j]*(r[j]-j-1)+m[r[j]];
    }
    longs max = 0, tmp; int pos = 0;
    for(int i=1;i<=n;++i)
        if((tmp=fl[i]+fr[i]+m[i])>max)
            max = tmp, pos = i;
    ans[pos] = m[pos];
    for(int i=pos-1;i>0;--i)
        ans[i] = min(m[i],ans[i+1]);
    for(int i=pos+1;i<=n;++i)
        ans[i] = min(m[i],ans[i-1]);
    for(int i=1;i<=n;++i)
        cout<<ans[i]<<' ';
    return 0;
}