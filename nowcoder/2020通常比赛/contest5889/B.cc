/**
 *
 * n方估计会死；怎么还答案错误的
 * 不对不对，这样DP好像不太行……
 * 害n2还是超时了……
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

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;

template <typename number>
int compareTo(number x) {return x < -eps ? -1 : x > eps;}
template <typename number>
int compareTo(number a, number b) {return compareTo(a-b);}

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

const int N = 1e5 + 5;
struct after{int a, b;} alice[N];
longs dp[N], ans = 0;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif
    int n, d; cin >> n >> d;
    for (int i = 0; i < n; ++ i)
        cin >> alice[i].a >> alice[i].b,
            dp[i] = alice[i].b;
    for (int i = 0; i < n; ++ i)
        for (int j = i + 1; j < n; ++ j)
            if (abs(alice[i].a - alice[j].a) <= d)
                dp[j] = max(dp[j], dp[i] + alice[j].b);
    for (int i = 0; i < n; ++ i)
        ans = max(dp[i], ans);
    cout << ans << endl;

    return 0;
}