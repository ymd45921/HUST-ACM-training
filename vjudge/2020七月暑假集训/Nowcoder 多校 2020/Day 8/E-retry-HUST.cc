/**
 * 
 * 一道很巧妙的题目；可以有很多种做法：
 * 至少现在我就已经知道有三种做法；
 * 
 * 这是其中的一种做法：来自校队 HUST-3
 * 
 * 看起来使用了质数筛；
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <bitset>

using namespace std;
using longs = long long;
using uint = unsigned;

inline int nextInt()
{
    int x = 0, f = 0, ch = getchar();
    while (!isdigit(ch)) ch == '-' && (f = !f), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 5;
bitset<N> isComp;
int prime[N], c[N], d[N];
longs f[N], sum[N];

void preProcess()
{
    auto &cnt = prime[0];
    for (int i = 2; i < N; ++ i)
    {
        if (!isComp[i]) prime[++ cnt] = i, d[i] = 2, c[i] = 1;
        for (int j = 1, x; j <= cnt && (x = i * prime[j]) < N; ++ j)
        {
            isComp[x] = true;
            if (i % prime[j]) c[x] = 1, d[x] = d[i] * 2;
            else 
            {
                c[x] = c[i] + 1;
                d[x] = d[i] / c[x] * (c[x] + 1);
                break;
            }
        }
    }
    f[6] = 1;
    for (int i = 7; i < N; ++ i)
        f[i] = f[i - 1] + d[i] - d[i - 1] + (i & 1 ? (i - 4) / 2 : 0);
    for (int i = 7; i < N; i += 2) ++ f[i];
    for (int i = 1; i < N; ++ i) sum[i] = sum[i - 1] + f[i];  
}

int main()
{
    ios::sync_with_stdio(false);
    
    preProcess();
    int t = nextInt();
    for (int i = 1; i <= t; ++ i)
    {
        int l = nextInt(), r = nextInt();
        auto ans = sum[r] - sum[l - 1];
        printf("Case #%d: %lld\n", i, ans);
    }  
    
    return 0;
}