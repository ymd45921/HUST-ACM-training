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
        return div<rhs.div;
    }
};

int n,a,b;
creature in[200050];
longs ans = 0;

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


}