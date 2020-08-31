/**
 * 
 * 相对运动确实能想象得到
 * 
 * 但是用扫描线是真的……绝了
 * 果然思维题。
 * 
 * 好吧，实现也是有讲究的。
 * 细节很多。
 * 
 * 这个是对着题解敲的代码
 */
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;
struct cloud {int x,y,p,q;};
enum lrb{lb=-1,rb=+1};
enum typ{a=0,b=1};
struct point
{
    int pos;
    lrb bound;
    typ type;
    inline bool operator<(const point& rhs) const;
    static void show(vector<point>& v);
};


int n,m;
cloud cl;
vector<point> scline;
longs cnt[2],ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        ans = 0ll;
        for(int i=0;i<m;++i)
        {
            cin>>cl.x>>cl.y>>cl.p>>cl.q;
            scline.push_back({cl.q-cl.p,rb,a});
            scline.push_back({cl.y-cl.x,lb,a});
        }
        for(int i=0;i<m;++i)
        {
            cin>>cl.x>>cl.y>>cl.p>>cl.q;
            scline.push_back({cl.q-cl.p,rb,b});
            scline.push_back({cl.y-cl.x,lb,b});
        }
        sort(scline.begin(),scline.end());
        point::show(scline);
        for(auto i:scline)
        {
            cnt[i.type] += i.bound;
            if(i.bound==rb) ans += cnt[i.type^1];
        }
        cout<<ans<<endl;
    }


    return 0;
}

bool point::operator<(const point& rhs) const
{
    if(pos==rhs.pos)
        if(bound==rhs.bound) return type<rhs.type;
        else return bound>rhs.bound;
    else return pos<rhs.pos;
}

void point::show(vector<point>& v)
{
    for(auto i:v)
    {
        if(i.type==a)
            if(i.bound==lb)cout<<']';
            else cout<<'[';
        else if(i.bound==rb)cout<<'{';
        else cout<<'}';
    }
    cout<<endl;
}