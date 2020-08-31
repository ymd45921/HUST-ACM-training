/**
 * 
 * 这个我竟然也想到了排序X，但是之后就没有想到了
 * 
 * 你想到的是遍历多次直到找完所有的木板
 * 但是实际上这种题目可以用离散数学里的Dilworth定理
 * 最小上升子序列组数等于最长下降子序列长度
 * 
 * 然后就是这个经典的最长单调子序列的DP求法
 * 但是经典的做法并不能直接得到具体的方案。
 * 
 * 把动规数组变成栈，真实想的出来……
 * 
 * 参考一下洛谷P1020，其实没有什么变化==
 */
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstring>

#define x first.first
#define y first.second
#define num second

using namespace std;
typedef long long longs;
typedef long double longd;
typedef pair<pair<int,int>,int> it;

it in[100010];
int n;
int ans[100010];    // 0是组数，1~n记录分组情况
int stack[100010];  // 记录不同组当前最大元素，其实也维护了最长的下降子序列

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        ans[0] = 0;
        memset(stack,0,sizeof(int)*(n+1));
        for(int i=1;i<=n;++i)
        {
            cin>>in[i].x>>in[i].y;
            in[i].num = i;
        }
        sort(in+1,in+1+n);
        for(int i=1;i<=n;++i)
        {
            // int lb=1,rb=ans[0];     // 在组数中二分查找第一个不大于当前木板宽的位置
            // while(lb<=rb)           // 可以使用STL的lower_bound带比较器，upper_bound这里好像也行。
            // {
            //     int mid = lb+rb >> 1;
            //     if(stack[mid]<in[i].y) rb = mid-1;
            //     else lb = mid+1;
            // }
            int lb = upper_bound(stack+1,stack+ans[0]+1,in[i].y,greater<int>())-stack;
            stack[lb] = in[i].y;
            if(lb>ans[0]) ans[0]=lb;
            ans[in[i].num] = lb;
        }
        cout<<ans[0]<<endl;
        for(int i=1;i<=n;++i)
        cout<<ans[i]<<' ';
    }
 
    return 0;
}