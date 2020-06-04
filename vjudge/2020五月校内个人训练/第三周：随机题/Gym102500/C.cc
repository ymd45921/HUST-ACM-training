/**
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#endif

#include <algorithm>
#include <cstring>
#include <vector>
#include <unordered_map>

#define inbound(p, c) (p >= c.first && p <= c.second)
#define AP ap.begin(), ap.end()

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

using canvas = pair<int, int>;
vector<canvas> ac;
vector<int> ap;
unordered_map<int, int> rp;

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
#endif

    int nc, np, l, r, x;
    bool failed = false;
    cin >> nc;
    while (nc --)
    {
        cin >> l >> r;
        if (!ac.empty() && ac.back().second == l) rp[l] = 1;
        ac.emplace_back(l, r);
    }
    nc = ac.size(); cin >> np;
    while (np --)
    {
        cin >> x;
        if (rp.count(x) && rp[x]) rp[x] = -1;
        ap.push_back(x);
    }
    np = ap.size(); bool p1 = false, p2 = false;
    vector<int> add;
    for (auto & ii : ac)
    {
        bool extend = (!add.empty() && add.back() == ii.first);
        auto ll = lower_bound(AP, ii.first);
        auto rr = upper_bound(AP, ii.second);
        int cnt = rr - ll;
        if (cnt > 2) { failed = true; break; }
        else if (cnt == 2)
        {
            if (extend)
            {
                if (p1) add.back() -= 2;
                else if (p2) add.back() -= 1;
                else add.back() -= 3;
            }
            auto xx = rr - 1;
            p1 = false, p2 = false;
            if (xx == ap.end()) continue;
            while (*xx >= ii.second - 3)
            {
                if (*xx == ii.second - 1) p1 = true;
                else if (*xx == ii.second - 2) p2 = true;
                -- xx;
                if (xx == ap.end()) break;
            }
        }
        else if (cnt < 2)
        {
            if (extend && cnt == 1) continue;
            else if ((extend && cnt == 0) || (!extend && cnt == 1))
            {
                auto iii = ii.second - (ii.second - 1 == *ll ? 2 : 1);
                if (rp.count(ii.second) && rp[ii.second] == -1)
                    add.push_back(iii);
                else add.push_back(ii.second);
            }
            else
            {
                add.push_back(ii.second - 4);
                add.push_back(ii.second);
            }
        }
    }
    if (!add.empty() && ac.back().second == ap.back())
        if (add.back() == ap.back()) -- add.back();
    if (failed) cout << "impossible" << endl;
    else
    {
        cout << add.size() << endl;
        for (auto & i : add) cout << i << ' ';
        cout << endl;
    }

    return 0;
}