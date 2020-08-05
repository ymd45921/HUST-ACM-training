/**
 *
 * 询问的 m ∈ k ∈ n
 * 说是 n 次询问，但是询问的东西本质和 n 无关
 * 样例其实已经在疯狂暗示了
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
#include <unordered_map>

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

#define ask cout << "? "
#define chk cout << "! "

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int n, k, pos, val;
    cin >> n >> k;
    unordered_map<int, int> x;
    const int lim = k + 1;
    int m_pos = -1, m_val = -1;
    for (int i = 1; i <= lim; ++ i)
    {
        ask;
        for (int j = 1; j <= lim; ++ j)
            if (j == i) continue;
            else cout << j << ' ';
        cout << endl;
        cin >> pos >> val;
        if (val > m_val) m_pos = pos, m_val = val;
        ++ x[pos];
    }
    chk << x[m_pos] << endl;

    return 0;
}