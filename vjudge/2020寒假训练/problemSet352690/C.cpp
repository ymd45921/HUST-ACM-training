/**
 * 
 * 贪心
 */
#include <iostream>
#include <utility>
#include <queue>

#define cost first
#define num second

using namespace std;
typedef pair<int,int> item;

int n,k,c[300010],ans[300010];
long long sum = 0;
priority_queue<item> heap;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;++i) cin>>c[i];

    int ptr = 1;
    item cur;
    for(int i=k+1;i<=k+n;++i)
    {
        for(;ptr<=n&&ptr<=i;++ptr)
            heap.push({c[ptr],ptr});
        cur = heap.top();
        heap.pop();
        ans[cur.num] = i;
        sum += (long long)cur.cost*(i-cur.num);
    }

    cout<<sum<<endl;
    for(int i=1;i<=n;++i)
    cout<<ans[i]<<' ';
    return 0;
}

