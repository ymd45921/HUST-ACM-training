/**
 *
 * 是傻逼吧（
 *
 * 不管了不管了，既然大家都用这个方法用就好了
 */
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>

#define ask cout<<"? "
#define chk cout<<"! "

using namespace std;
using longs = long long;

constexpr int inf = 0x3f3f3f3f;
constexpr double eps = 1e-8;

template <int n> const int *EulerSieve()
{
    static int prime[n + 5];
    bool vis[n + 5] {false};
    int &cnt = prime[0] = 0;
    for (int i = 2; i <= n; ++ i)
    {
        if (!vis[i]) prime[++ cnt] = i;
        for (int j = 1; j <= cnt && (longs)i * prime[j] <= n; ++ j)
        {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    return prime;
}

struct triple
{
    int p, a;
    longs v;

    triple(int p, int a, longs v) : p(p), a(a), v(v) {}

    bool operator<(const triple &rhs) const
    {
        if (a == rhs.a) return v > rhs.v;
        else return a < rhs.a;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    longs response, ans;
    auto p = EulerSieve<31623>();
    auto cnt = p[0];
    cin >> t;
    while (t --)
    {
        priority_queue<triple> pq;
        for (int i = 1; i <= cnt; ++ i)
            pq.push({p[i], 1, p[i]});
        vector<triple> used; ans = 1;
        for (int i = 0; i < 22; ++ i)
        {
            used.clear();
            longs query = 1;
            while (!pq.empty())
            {
                auto &front = pq.top();
                if ((double)query * front.v > 1e18) break;
                used.push_back(front);
                query *= front.v; pq.pop();
            }
            ask << query << endl; cin >> response;
            for (auto &ii : used) if (response % ii.v == 0)
                {
                    ans = (ans / ii.a) * ++ ii.a;
                    ii.v *= ii.p; pq.push(ii);
                }
        }
        chk << ans * 2 << endl;
    }

    return 0;
}