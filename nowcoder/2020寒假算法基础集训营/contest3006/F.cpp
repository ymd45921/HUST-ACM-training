/**
 * 
 * 这题是个DP是真的万万没想到==
 * 
 * 不如说读题的时候RJ->AC这个条件根本就没有有效利用。
 * 也就是说必不会出现连续RJ，一发RJ后必连AC
 * 
 * 当第i句话是AC时，它可以从i-1的AC或者有意义的i-x的RJ转移
 * 或者，当第i句话时RJ时，它只能从i-1的AC转移
 * 建立这样的DP[2][]数组进行转移即可
 * 
 * 多次询问大概率要用前缀和之类的优化，那就做呗
 * 
 * 奇了怪了，为什么本地测试输出的答案正确传上去就不行了？
 * GNU和Clang的区别嘛？
 * 草，换成了G++就真jb过了，看来是clang++分配新内存不初始化的原因？这也不应该啊
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

const longs MOD = 1000000007ll;

int x,q,l,r;
int dp[2][100010];
int pre[100010];

inline void preProcess(int x)
{
    const int AC=1,RJ=0;
    dp[RJ][0] = 0;
    dp[AC][0] = 1; 
    pre[0] = 1;
    for(int i=1;i<=100010;++i)
    {
        dp[RJ][i] = (i>=x)?dp[AC][i-x]:0;
        dp[AC][i] = ((longs)dp[RJ][i-1]+dp[AC][i-1])%MOD;
        pre[i] = ((longs)dp[AC][i]+dp[RJ][i]+pre[i-1])%MOD;
    }
}

int solution(int l,int r)
{
    return (pre[r]-pre[l-1]+MOD)%MOD;   
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>x>>q)
    {
        preProcess(x);
        while(q--)
        {
            cin>>l>>r;
            cout<<solution(l,r)<<endl;
        }
    }

    return 0;
}