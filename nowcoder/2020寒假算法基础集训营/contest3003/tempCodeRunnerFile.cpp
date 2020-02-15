/**
 * 
 * 一说起异或，你不知道的就太多了
 * 
 * 首先要去重：相同的点之间代价为0.
 * 然后就如你所想：找到最小的二进制位k——一定有vi这k位是1而其他vj的k位是0
 * 这样的话：答案就是所有vj和vi连接，得到lowbit是(1<<k)*(#V-1)
 */
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
int v[200050];
set<int> vertex;

int lowbit(int val)
{
    if(!val) return 0;
    int ans = 1;
    while(!(val&1))
    {
        val >>= 1;
        ans <<= 1;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        vertex.clear();
        longs lowest = 1<<60;
        for(int i=1;i<=n;++i)
        {
            cin>>v[i];
            vertex.insert(v[i]);
            lowest = min(lowest,(longs)lowbit(v[i]));
        }
        cout<<lowest*(vertex.size()-1)<<endl;
    }

    return 0;
}