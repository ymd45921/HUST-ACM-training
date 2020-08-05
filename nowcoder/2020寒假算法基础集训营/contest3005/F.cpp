/**
 * 
 * 一开始还以为是LCA
 * 
 * 仔细思考：
 * 无路可走——唯一的出路上站着对方——只有一条出路——在叶子上
 * 又因为题目给的树是一颗完全树，那更是这样
 * 
 * 整个题目中不变的是两人距离的奇偶性——要将另一方逼到叶子处
 * 必须距离是偶数。
 * 然后统计两人距离是偶数的情况，可以统计节点深度：
 * 两个节点深度的奇偶性相同那么之间的距离就是偶数
 * 否则就是奇数。
 * 
 * 这…………我确实想不到==
 * 
 * 日，怎么还能WA的（）
 * 果然还是long long的问题，乘法先算就算+0ll也没用啊//
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
longs odd,even;
int p[1000010]{0};
int depth[1000010]{0};

void count(int x)
{
    if(x==1||depth[x]) return;
    count(p[x]);
    depth[x] = depth[p[x]]+1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(depth,0,sizeof(int)*(n+1));
        depth[1] = p[1] = 0;
        odd = even = 0;
        longs ans = 0;
        for(int i=2;i<=n;++i)
            cin>>p[i];
        for(int i=2;i<=n;++i)
            count(i);
        for(int i=1;i<=n;++i)
            if(depth[i]&1) ++odd;
            else ++even;
        ans = even*(even-1)+odd*(odd-1);
        cout<<ans<<endl;
    }

    return 0;
}