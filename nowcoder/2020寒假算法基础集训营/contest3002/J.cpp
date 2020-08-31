/**
 *
 * 是不是如果是乘法的话矩阵快速幂就束手无策了啊
 *
 * 是个斐波拉契数列，而快速斐波拉契可以矩阵快速幂
 * f(i) = c^(fib(i)-1) * f(1)^fib(i-2) * f(2)^fib(i-1)
 * 
 * 0,输出负数的问题已经解决，还是WA
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

const int MOD = 1000000007;
longs a,b,c,n,x,y;
longs fib[2][2];

inline int power(longs a,longs b)
{
    longs ans = 1;
    while(b)
    {
        if(b&1) ans = (ans*a)%MOD;
        a = (a*a)%MOD;
        b>>=1;
    }
    return ans;
}

void multiMatrix(longs m1[2][2],longs m2[2][2])
{
    longs ans[2][2]{0};
    for(int i=0;i<2;++i)
        for(int j=0;j<2;++j)
        {
            for(int k=0;k<2;++k)
                ans[i][j] += m1[i][k]*m2[k][j];
            ans[i][j] %= MOD;
        }
    memcpy(m1,ans,sizeof(ans));
}

longs ffib(longs n)
{
    longs trans[2][2] = {{1,1},{1,0}};
    longs x = n-1;
    memset(fib,0,sizeof fib);
    fib[0][0] = fib[1][1] = 1;
    while(x)
    {
        if(x&1L) multiMatrix(fib,trans);
        multiMatrix(trans,trans);
        x >>= 1;
    }
    return fib[0][0];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>x>>y>>a>>b)
    {
        c = power(a,b);
        ffib(n);
        longs ans = power(c,fib[0][0]-1);
        ans *= power(x,fib[1][1]);
        ans %= MOD;
        ans *= power(y,fib[1][0]);
        ans %= MOD;
        cout<<(int)ans<<endl;
    }

    return 0;
}