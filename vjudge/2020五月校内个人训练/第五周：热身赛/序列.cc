/**
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

const int mod = 1e9 + 9, N = 100;
int t[N], n, k;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif
    cin >> n >> k;
    for (int i = 0; i < n; ++ i)
        cin >> t[i];


    return 0;
}