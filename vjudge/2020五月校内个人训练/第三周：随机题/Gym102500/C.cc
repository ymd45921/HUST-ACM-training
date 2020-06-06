/**
 *
 * 这样，虽然开销大了点（毕竟 STL map 遍历
 * 但是看起来代码更加直观，也不太容易出奇怪的错误
 *
 */
#define USING_STDIO 0
#if USING_STDIO
#include <cstdio>
#else
#include <iostream>
#endif

#include <algorithm>
#include <vector>
#include <unordered_map>

#define Vec(x) (x).begin(), (x).end()

using namespace std;

const int N = 1050;

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
int cnt[N];

int main()
{
#if !USING_STDIO
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif

    int nc, np, l, r, x;
    unordered_map<int, bool> vp;
    bool failed = false;
    cin >> nc;
    while (nc --)
    {
        cin >> l >> r;
        ac.emplace_back(l, r);
    }
    nc = ac.size(); cin >> np;
    while (np --)
    {
        cin >> x;
        ap.push_back(x);
        vp[x] = true;
    }
    np = ap.size();
    vector<int> add;
    for (int i = 0; i < nc; ++ i)
    {
        auto &ii = ac[i];
        cnt[i] = upper_bound(Vec(ap), ii.second) - lower_bound(Vec(ap), ii.first);
        if (cnt[i] > 2) {failed = true; break;}
    }
    if (!failed) for (int i = 0; i < nc - 1; ++ i)
    {
        if (cnt[i] == 2) continue;
        auto &ii = ac[i];
        if (cnt[i + 1] >= 2 || vp[ii.second] || ii.second != ac[i + 1].first)
            for (int j = ii.first + 1; j < ii.second && cnt[i] < 2; ++ j)
            {   if (!vp.count(j)) {add.push_back(j); ++ cnt[i]; vp[j] = true;}  }
        else
        {
            add.push_back(ii.second);
            ++ cnt[i], ++ cnt[i + 1];
            for (int j = ii.first + 1; j < ii.second && cnt[i] < 2; ++ j)
                if (!vp.count(j)) {add.push_back(j); ++ cnt[i]; vp[j] = true;}
        }
    }
    auto &bk = ac[nc - 1];
    if (!failed) for (int i = bk.first + 1; i <= bk.second && cnt[nc - 1] < 2; ++ i)
        if (!vp.count(i)) { add.push_back(i); ++ cnt[nc - 1]; vp[i] = true; }
    if (failed) cout << "impossible" << endl;
    else
    {
        cout << add.size() << endl;
        sort(Vec(add));
        for (auto ii : add) cout << ii << ' ';
        cout << endl;
    }

    return 0;
}