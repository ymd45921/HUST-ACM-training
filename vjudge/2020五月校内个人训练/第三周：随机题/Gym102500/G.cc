/**
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#include <iomanip>
#endif

#include <algorithm>
#include <cstring>

using namespace std;
typedef long long longs;
using number = long double;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 505;

int compareTo(number x) {return x < -eps ? -1 : x > eps;}
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

int n, k;
number s[N], ss[N];

inline number sum(int l, int r)
{
    if (l == r) return s[l];
    else if (l < r) 
        if (l >= 1 && r <= n) return ss[r] - ss[l - 1];
        else return sum(n + l, n) + sum(1, r);
    else return sum(l, n) + sum(1, r);
}

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    cin >> n >> k;
    for (int i = 0; i <= n; ++ i)
        cin >> s[i], ss[i] = ss[i - 1] + s[i];

    return 0;
}