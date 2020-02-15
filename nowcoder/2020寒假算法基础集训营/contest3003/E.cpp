/**
 * 
 * 原来的想法：这三元组和k没啥关系，主要就是ij
 * 确实就是纯粹的小于n的整数的因数个数
 * 这样的话枚举还是挺麻烦的。我甚至寻思了筛
 * 
 * 题解注：一看到根号就马上想到平方。然后这题就出来了
 * 
 * 平方可以得到 i*j = v^2 < n，一定程度上减少了暴力枚举的复杂度
 * 这样就能做了==
 * 确实比我那种一开始直接无视k要舒服一点
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n;
int cnt;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        longs ll;
        cnt = 0;
        for(int i=1;(ll=i*i)<=n;++i)
        {
            for(int j=1;j<i;++j)
            {
                if(ll/j*j==ll) cnt+=2;  // 这里敲错实属dd
            }
            ++cnt;
        }
        cout<<cnt<<endl;
    }

    return 0;
}