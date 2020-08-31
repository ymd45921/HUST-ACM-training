/**
 * 
 * 用了前缀和还是T了
 * 
 * 如果找到了每个最小的段，用来计算所有0段？
 * 
 * 确实要用前缀和，但是不是在前缀和上遍历
 * 若有段[l,r]符合，那么pre[l-1]=pre[r]，所以需要统计前缀和相同的情况。
 * 虽然前缀和出来的东西可以很大，但是这个可以Map……
 * 
 * 这map好好用啊== 就和JavaScript的对象一样好用。
 * 
 * 最后卡91.3%的原因：答案会爆int，要使用long long
 */
#include <iostream>
#include <map>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
int in[200050]{0};
int pre[200050]{0};
longs tmp,cnt;
int s,t;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        cnt = 0;
        map<int,int> stat;
        stat[0] = 1;            // 前缀和为0可以直接作为答案
        for(int i=1;i<=n;++i)
        {
            cin>>in[i];
            pre[i] = pre[i-1]^in[i];
            cnt += stat[pre[i]];
            ++stat[pre[i]];
        }
        cout<<cnt<<endl;
    }

    return 0;
}