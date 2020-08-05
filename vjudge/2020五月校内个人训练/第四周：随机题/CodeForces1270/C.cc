/**
 *
 * 人类智慧
 *
 * 还有使用一个数字解决的方法，那是不是通用做法呢？
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
typedef unsigned long long ulongs;

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

const int N = 1e5 + 5;
ulongs a[N], sum, x_sum;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int t, n; cin >> t;
    while (t --)
    {
        cin >> n;
        sum = x_sum = 0;
        for (int i = 1; i <= n; ++ i)
        {
            cin >> a[i];
            sum += a[i];
            x_sum ^= a[i];
        }
        if ((x_sum << 1u) == sum)
            cout << 0 << endl << endl;
        else cout << 2 << endl << x_sum
            << ' ' << (x_sum + sum) << endl;
    }

    return 0;
}