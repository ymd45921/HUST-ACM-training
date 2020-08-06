/**
 *
 * 虽然乍一看毫无头绪，但是仔细分析还是有很多规律
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
    while (!isdigit(ch)) ch == '-' && (f = 1), ch = getchar();
    while (isdigit(ch)) x = x * 10 + ch - 48, ch = getchar();
    return f ? -x : x;
}

const int N = 1e5 + 5;
const longs mod = 1e9 + 7;
longs pow2[N];
bitset<N> a;

void preProcess()
{
    pow2[0] = 1;
    for (int i = 1; i < N; ++ i)
        pow2[i] = pow2[i - 1] * 2 % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    
    preProcess();
    int t = nextInt();
    while (t --)
    {
        int n = nextInt(), m = nextInt();
        a.reset();
        for (int i = 1; i <= n; ++ i) 
            if (nextInt() == '1') a[i] = true;
        while (m --)
        {
            int u = nextInt(), v = nextInt();
            
        }
    }


    return 0;
}