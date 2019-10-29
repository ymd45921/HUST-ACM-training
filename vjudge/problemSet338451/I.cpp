#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
struct order
{
    int q,d;
    bool operator<(const order&rhs) const           //用于构造大顶堆，想要弹出的是花费时间最大的任务。
    {
        return q<rhs.q;
    }
};
int n,t;
order in[800080];
struct cmp
{
    bool operator()(order&a, order&b) const         //用于sort排序，优先选择结束时间靠前的项并置前。
    {
        return a.d<b.d||(a.d==b.d&&a.q<b.q);
    }
};

priority_queue<order> table;
int cost;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    while(t--)
    {
        while(!table.empty())table.pop();           //清理历史遗留问题

        cin>>n;
        for(int i=0;i<n;++i)cin>>in[i].q>>in[i].d;
        sort(in,in+n,cmp());

        cost = 0;
        for(int i=0;i<n;++i)
        {
            if(cost+in[i].q<=in[i].d)
            {
                cost+=in[i].q;
                table.push(in[i]);
            }
            else if(!table.empty())
            {
                if(table.top().q>in[i].q)
                {
                    cost-=table.top().q;
                    table.pop();
                    cost+=in[i].q;
                    table.push(in[i]);
                }
            }
        }
        cout<<table.size()<<endl;
    }

    return 0;
}