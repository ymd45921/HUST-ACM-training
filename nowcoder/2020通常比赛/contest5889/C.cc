/**
 *
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#include <cctype>
#else
#include <iostream>
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

const int N = 105;
vector<unsigned> e, o;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    unsigned n, a; cin >> n;
    unsigned even = 0, odd = 0, sum = 0, tmp = 0;
    for (int i = 0; i < n; ++ i)
    {
        cin >> a;
        if (a & 1u)
        {
            ++ odd;
            o.push_back(a);
            tmp += a;
        } else
        {
            ++ even;
            e.push_back(a);
            sum += a;
        }
    }
    sort(o.begin(), o.end());
    if (odd & 1u) sum += tmp - o[0];
    else sum += tmp;
    cout << sum << endl;
    
    return 0;
}