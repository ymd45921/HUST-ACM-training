#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

const int N = 1e6 + 5;
const int Q = 25005;

inline int nextInt()
{
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}

struct triple
{
    int l, r, v;

    bool operator< (const triple &rhs) const
    {
        if(v == rhs.v) return l < rhs.l;
        else return v > rhs.v;
    }
} query[Q], xx[Q];

namespace UFS
{
    typedef int number;
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

bool check(int mid)
{
    for (int i = 1; i <= mid; ++ i)
        xx[i] = query[i];
    sort(xx + 1, xx + 1 + mid);
    int now = xx[1].v, lmax, lmin, rmax, rmin;
    lmin = lmax = xx[1].l, rmin = rmax = xx[1].r;
    for (int i = 2; i <= mid; ++ i)
        if (now == xx[i].v)
        {
            lmin = min(lmin, xx[i].l);
            rmin = min(rmin, xx[i].r);
            lmax = max(lmax, xx[i].l);
            rmax = max(rmax, xx[i].r);
            if (lmax > rmin) return false;
        }
        else
        {
            if (UFS::father(lmax) > rmin) return false;
            for (int j = UFS::father(lmin);; j = UFS::father(j + 1))
                if (j > rmax) break;
                else UFS::join(j, j + 1);   // Join 是对的，但是速度更慢；直接改吧
            now = xx[i].v;
            lmin = lmax = xx[i].l, rmin = rmax = xx[i].r;
        }
    return UFS::father(lmax) <= rmin;
}

int main()
{
//    freopen(R"(D:\shiroha\Downloads\P2898_9.in)", "r", stdin);
    int n, q, ll, rr, vv;
    n = nextInt(), q = nextInt();
    for (int i = 1; i <= q; ++ i)
        query[i].l = nextInt(),
        query[i].r = nextInt(),
        query[i].v = nextInt();
    ll = 0, rr = q + 1;
    while (ll < rr - 1)
    {
        int mid = ll + rr >> 1u;
        UFS::init(n + 2);   // 这里得 +2
        if (check(mid)) ll = mid;
        else rr = mid;
    }
    vv = (rr > q ? 0 : rr);
    printf("%d\n", vv);

    return 0;
}