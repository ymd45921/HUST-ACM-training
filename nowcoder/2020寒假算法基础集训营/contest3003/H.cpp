/**
 * 
 * 原来这种DP叫做划分DP啊……
 * 但是看题解倒也不是传统的划分DP
 * 
 * 初见42.86%：DP不对，你这有后效啊
 * 有一部分的可能性被完全忽略了。
 * 而且就从最先端和最后端要特判就不对劲
 * 
 * 怎么还有至少k个元素这个条件
 * 瞬间觉得麻烦了起来
 * 
 * 好，这个题目确实有点东西
 * 
 * dp：要不贴贴，要不拉拉
 */
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,k;
int a[300050];
int d[300050];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>k)
    {
        for(int i=0;i<n;++i) cin>>a[i];
        sort(a,a+n);
        int ans = 0;
        
        const int N = n-1;
        memset(d,0x3f,sizeof(d));
        d[k-1] = a[k-1]-a[0];
        for(int i=k;i<n;++i)
        {
            d[i] = min(d[i-1]-a[i-1]+a[i],d[i-k]+a[i]-a[i-k+1]);
        }
        ans = d[n-1];

        cout<<ans<<endl;
    }

    return 0;
}