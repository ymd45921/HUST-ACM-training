/**
 *
 * 传说中的 sac 题
 *
 * gcd(a, b) = 1 <=> gcd(a + b, ab) = 1
 * 这么明说的话还是挺好想的，只要找出 a, b > 1 且是约数就好了
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
#include <bitset>

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

const int N = 5e5 + 5;
const int A = 1e7 + 5;
int a[N], d1[N], d2[N], low[A];

template <int A> vector<int> &EulerSieve()
{
    static vector<int> prime;
    bitset<A> vis;
    low[0] = 0, low[1] = 1;
    for (int i = 2; i <= A; ++ i)
    {
        if (!vis[i]) prime.push_back(i), low[i] = i;
        for (auto & pp : prime)
        {
            if ((longs)i * pp > A) break;
            vis[i * pp] = true;
            low[i * pp] = pp;
            if (i % pp == 0) break;
        }
    }
    return prime;
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    const auto raw = EulerSieve<A>();
    int n; cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i];
        int xx = 1, tmp = a[i];
        if (low[a[i]] != 1 && low[a[i]] != a[i])
            while (tmp % low[a[i]] == 0)
                tmp /= low[a[i]], xx *= low[a[i]];
        if (xx == 1 || tmp == 1) d1[i] = d2[i] = -1;
        else d1[i] = xx, d2[i] = tmp;
    }
    for (int i = 1; i <= n; ++ i) cout << d1[i] << ' ';
    cout << endl;
    for (int i = 1; i <= n; ++ i) cout << d2[i] << ' ';
    cout << endl;

    return 0;
}