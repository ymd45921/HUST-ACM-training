#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned long long ulongs;
struct edge
{
    int u,v;
    ulongs w;

    bool operator<(const edge& rhs) const
    {
        if (w != rhs.w) return w < rhs.w;
        else if (u != rhs.u) return u < rhs.u;
        else return v < rhs.v;
    }

    bool operator==(const edge& rhs) const
    {
        return u == rhs.u &&
               v == rhs.v &&
               w == rhs.w;
    }
};

const int N = 100010;
const ulongs mod = 1e9 + 7;

int m, n, f[N];
ulongs k1, k2;
edge e[N];

inline int father(int x)
{
    return x == f[x] ? x : f[x]= father(f[x]);
}

ulongs xorShift128Plus()
{
    ulongs k3=k1,k4=k2;
    k1 = k4;
    k3 ^= k3<<23;
    k2 = k3^k4^(k3>>17)^(k4>>26);
    return k2+k4;
}

void gen()
{
    cin >> n >> m >> k1 >> k2;
    for (int i=1; i<=n; ++i) f[i] = i;
    for (int i=1; i<=m; ++i)
    {
        e[i].u = xorShift128Plus() % n + 1;
        e[i].v = xorShift128Plus() % n + 1;
        e[i].w = xorShift128Plus();
        if (e[i].u > e[i].v) swap(e[i].u,e[i].v);
    }
}

ulongs kurskal()
{
    sort(e+1, e+1+m);
    int cnt = 0;
    ulongs cost = 0,time = 1,res;
    for (int i=1; i<=m; i++)
    {
        int fu = father(e[i].u),
            fv = father(e[i].v);
        if (fu != fv)
        {
            res = 1;
            f[fu] = fv;
            cost = (cost + e[i].w) % mod;
            ++cnt;
            while (i+1 <= m && e[i] == e[i+1])
            {
                ++i;
                ++res;
            }
            time = time * res % mod;
        }
        if (cnt == n-1) break;
    }
    return cnt == n-1 ? cost % mod * time % mod : 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--)
    {
        gen();
        ulongs ans = kurskal();
        cout << ans << endl;
    }
    return 0;
}