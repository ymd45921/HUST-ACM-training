/**
 *
 * 道理我都懂，为什么一定要倒着来查呢
 * 顺着找，最大的障碍在于统计输出答案
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#endif

#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;
typedef long long longs;

const int inf = 0x3f3f3f3f;
const double eps = 1e-8;
const int N = 2e5 + 5;

#if USING_STDIO
inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
#endif

namespace UFS
{
    using number = int;
    number p[N];

    void init(int n = N)
    {
        for (int i = 0; i < n; ++ i)
            p[i] = i;
    }

    number father(int x)
    {
        return p[x] == x ? x : p[x] = father(p[x]);
    }

    number join(int x, int y)
    {
        return p[father(x)] = p[father(y)];
    }
}

int x[N], y[N], r[N], cnt = 0;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int n, m, d;
    cin >> n;
    UFS::init(n + 1);
    unordered_map<int, vector<unsigned>> xx;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> m;
        while (m --)
        {
            cin >> d;
            xx[d].push_back(i);
        }
    }
    using namespace UFS;
    for (auto & ii : xx)
    {
        auto &vec = ii.second;
        auto home = vec[0], siz = vec.size();
        if (siz <= 1) continue;
        for (int i = 1; i < siz; ++ i)
            if (father(vec[i]) != father(home))
            {
                join(vec[i], home);
                r[++ cnt] = ii.first;
                x[cnt] = vec[i], y[cnt] = home;
            }
    }
    bool connect = true;
    for (int i = 2; i <= n; ++ i)
        if (father(i) != father(1)) connect = false;
    if (!connect) cout << "impossible" << endl;
    else for (int i = 1; i < n; ++ i)
        cout << x[i] << ' ' << y[i] << ' ' << r[i] << endl;

    return 0;
}