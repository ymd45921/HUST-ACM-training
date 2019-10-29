#include <iostream>
#include <algorithm>

#define hp(i) in[i].hp
#define dmg(i) in[i].dmg
#define div(i) in[i].div

using namespace std;
typedef long long longs;

struct creature
{
    longs hp,dmg;
    longs div;

    bool operator<(const creature& rhs) const
    {
        return div>rhs.div;
    }
};

int n,a,b;
creature in[200050];
longs ans = 0;
int it,use;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n>>a>>b;
    for(int i=0;i<n;++i)
    {
        cin>>hp(i)>>dmg(i);
        div(i) = hp(i)-dmg(i);
    }
    sort(in,in+n);
    use = b;
    for(int i=0;i<n;++i)
    {
        if(use&&hp(i)>dmg(i))
        {
            dmg(i)=hp(i);
            --use;
        }
        ans+=dmg(i);
    }

    it = b-use;
    int icur = it-1;
    in[n] = {0,0,0};
    longs dx = 0;

    if(b&&a)
        for(int i=0;i<n;++i)
        {
            longs tmp = (hp(i)<<a) - dmg(i);
            if(use)
                dx = dx>tmp?dx:tmp;
            else if(i<it)
                dx = tmp>dx?tmp:dx;
            else
                dx = (tmp-div(icur)>dx)?tmp-div(icur):dx;
        }

    cout<<ans+dx;
    return 0;
}