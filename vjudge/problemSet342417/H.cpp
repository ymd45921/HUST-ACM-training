/* 
 * 等等，为什么题解只是DFS？？这不是DP题目的吗？？
 * 
 * WA - 1：等等，我裤子都脱了你就让我原地升天？答案怎么就大了1呢？
 *         草，题目理解错了，可以小于等于而不是小于，恁您娘（）
 */
#include <iostream>
#include <cstring>
#include <vector>

#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)

using namespace std;
const int maxIn = 100050;
typedef long long longs;
struct node
{
    int val;
    node* super;
    int edge;
    vector<node*> child;
};

int n;
node in[maxIn];
int tmpp,tmpc;

int ans = 0;

int treeSize(const node& tree)
{
    int res = 1;
    for(node* subtree : tree.child)
        res+=treeSize(*subtree);
    return res;
}

void dfs(const node& tree, int sum)
{
    if(sum<=tree.val)
    {
        int nextSum = max(sum,0);
        for(node* subtree : tree.child)
        {
            dfs(*subtree, nextSum+subtree->edge);
        }
    }
    else
    {
        ans+=treeSize(tree);
        return;
    }  
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;++i)cin>>in[i].val;
    for(int i=2;i<=n;++i)
    {
        cin>>tmpp>>tmpc;
        in[i].super = &in[tmpp];
        in[i].edge = tmpc;
        in[i].super->child.push_back(&in[i]);
    }

    dfs(in[1],-1);
    cout << ans;

    return 0;
}