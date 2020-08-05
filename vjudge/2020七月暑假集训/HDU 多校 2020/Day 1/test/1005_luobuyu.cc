#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
typedef long long LL;
const int N = 1e5 + 10;
const LL MOD = 1e9 + 9;

LL fac[N],A[N],B[N];
LL n,k,c;
void Init()
{
    fac[0] = 1;
    for(int i=1; i<N; i++)
        fac[i] = fac[i-1] * i % MOD;
    A[0] = B[0] = 1;
    for(int i=1; i<N; i++)
    {
        A[i] = A[i-1] * 691504013 % MOD;
        B[i] = B[i-1] * 308495997 % MOD;
    }
}

LL quick_mod(LL a,LL b,LL MOD)
{
    LL ans = 1;
    a %= MOD;
    while(b)
    {
        if(b & 1)
        {
            ans = ans * a % MOD;
            b--;
        }
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}

LL Solve(LL n,LL k,LL c1)
{
    LL ans = 0;
    for(int r=0; r<=k; r++)
    {
        LL t = A[k-r] * B[r] % MOD;
        t = quick_mod(t, c1, MOD);
        LL x = fac[k];
        LL y = fac[k-r] * fac[r] % MOD;
        LL c = x * quick_mod(y,MOD-2,MOD) % MOD;
        LL tmp = t * (quick_mod(t,n,MOD) - 1) % MOD * quick_mod(t-1,MOD-2,MOD) % MOD;
        if(t == 1) tmp = n % MOD;
        tmp = tmp * c % MOD;
        if(r & 1) ans -= tmp;
        else      ans += tmp;
        ans %= MOD;
    }
    LL m = quick_mod(383008016,MOD-2,MOD);
    ans = ans * quick_mod(m,k,MOD) % MOD;
    ans = (ans % MOD + MOD) % MOD;
    return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif // ONLINE_JUDGE
    int T;

    Init();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld %lld %lld", &n, &c, &k);
        printf("%lld\n", Solve(n, k, c));
    }
    return 0;
}