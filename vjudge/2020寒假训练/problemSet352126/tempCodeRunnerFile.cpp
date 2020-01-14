/**
 * 我日我怎么觉得这个题目是模拟啊==
 * 看样子有点像要用线段树的样子（）
 *
 * 模拟了就TLE了……果然不是模拟啊==
 */
#include <iostream>
#include <cstring>

#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
#define isleaf(x) (!(x.l-x.r))

using namespace std;

struct node
{
    int l,r;
    int v;
};

int n,a,b,N;
node tree[400020];

void buildTree(int pos,int upper,int lower)
{
    tree[pos] = {upper,lower,0};
    if(upper-lower)
    {
        int mid = (upper+lower)>>1;
        buildTree(lc(pos),upper,mid);
        buildTree(rc(pos),mid+1,lower);
    }
}

inline int getAns(int index)
{
    int cur = 0,mid,ans = 0;
    while(!isleaf(tree[cur]))
    {
        ans += tree[cur].v;
        mid = (tree[cur].l+tree[cur].r)>>1;
        if(index>mid)cur = rc(cur);
        else cur = lc(cur);
    }
    ans += tree[cur].v;
    return ans;
}

inline void color(int pos,int left,int right)
{
    if(tree[pos].l>=left&&tree[pos].r<=right)
    {
        ++tree[pos].v;
        return;
    }
    int mid = (tree[pos].l+tree[pos].r)>>1;
    if(left<=mid)color(lc(pos),left,mid);
    if(right>mid)color(rc(pos),mid+1,right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        if(!n)break;
        memset(tree,0,sizeof(tree));
        buildTree(0,1,n);
        N=n;
        while(n--)
        {
            cin>>a>>b;
            color(0,a,b);
        }
        cout<<getAns(1);
        for(int i=2;i<=N;++i)
            cout<<' '<<getAns(i);
        cout<<endl;
    }

    return 0;
}