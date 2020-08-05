#include <iostream>
#include <algorithm>

using namespace std;
typedef long long longs;

struct tile
{
    int n,p,h;
    bool operator<(const tile& rhs) const;
};

bool cmp(const tile& lhs, const tile& rhs)
{
    if(lhs.p==rhs.p) return lhs.h > rhs.h;
    else return lhs.p < rhs.p;
}

const int N = 5e5+5;

int n;
tile t[2][N];

inline bool scoll(int i)
{
    if(t[1][i].h >= t[0][i].h) return false;
    int v = t[1][i].p, hh = t[0][i].h;
    int ii;
    for(ii = i+1;ii<=n;++ii)
        if(t[1][ii].p != v || t[1][ii].h >= hh)
        {-- ii; break;}
    if(ii > n) -- ii;
    if(ii == i) return true;
    tile now = t[1][ii];
    for(int iii = ii; iii > i; --iii)
        t[1][iii] = t[1][iii-1];
    t[1][i] = now;
    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen(R"(D:\shiroha\Downloads\icpc2019data (1).tar\icpc2019data (1)\icpc2019data\A-azulejos\secret-21.in)","r",stdin);

    cin>>n;
    for(int i=1;i<=n;++i)
        t[0][i].n = t[1][i].n = i;
    for(int i=1;i<=n;++i)
        cin>>t[0][i].p;
    for(int i=1;i<=n;++i)
        cin>>t[0][i].h;
    for(int i=1;i<=n;++i)
        cin>>t[1][i].p;
    for(int i=1;i<=n;++i)
        cin>>t[1][i].h;
    sort(t[0]+1,t[0]+1+n,cmp);
    sort(t[1]+1,t[1]+1+n);
    bool ok = true;
    for(int i = 1; i <= n; ++ i)
        if(!scoll(i))
        {ok = false; break;}

    if(ok)
    {
        for(int i=1;i<=n;++i)
            cout<<t[0][i].n<<' ';
        cout<<endl;
        for(int i=1;i<=n;++i)
            cout<<t[1][i].n<<' ';
    }
    else cout<<"impossible";

    return 0;
}

bool tile::operator<(const tile& rhs) const
{
    if(p==rhs.p) return h < rhs.h;
    else return p < rhs.p;
}