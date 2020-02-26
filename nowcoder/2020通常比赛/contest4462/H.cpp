/**
 * 区间加减，等于说是要用差分数组；
 * 求处理之后的最大值，看起来树状数组说不定不行
 * 可能得上线段树。
 *
 * 因为同一个货物可能会多次进货，所以需要预处理
 *
 * 线段树还是一种比较稳妥的做法，可以维护一个max值
 *
 * 不过就算全体STL也是一个麻烦的题目啊（）
 * 我写炸了==
 */
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <sstream>
#include <cstring>

using namespace std;
typedef long long longs;
typedef long double longd;

struct range
{
    int l,r;
    bool operator<(const range &ths) const;
};

const int N = 1e5+10;
int dis[N];

void make_union(set<range> &r,range a)
{
    if(r.empty())
    {
        r.insert(a);
        return;
    }
    auto ub = r.lower_bound(a);
    auto re = r.end();
    if(ub==r.end());
    else while(ub->l<=a.r)
        {
            if(ub->r>a.r)
                a.r = ub->r;
            r.erase(ub++);
            if(ub==re) break;
        }
    if(ub!=r.begin())
    {
        --ub;
        if(ub->r>=a.l)
        {
            a.l = ub->l;
            r.erase(ub);
        }
    }
    r.insert(a);
}

const string print_union(set<range> &s)
{
    if(s.empty()) return "<0>";
    stringstream ss;
    int cnt = 0;
    for(auto a : s)
    {
        if(cnt++) ss<<" U ";
        if(a.l==a.r) ss<<'{'<<a.r<<'}';
        else ss<<"["<<a.l<<","<<a.r<<"]";
    }
    return ss.str();
}

inline void add_range(range &r, int v)
{
    dis[r.l] += v;
    dis[r.r+1] -= v;
}

const string print_range(range &r)
{
    stringstream ss;
    if(r.l==r.r) ss<<'{'<<r.r<<'}';
    else ss<<'['<<r.l<<','<<r.r<<']';
    return ss.str();
}

inline void print_array(int n)
{
    int now = 0;
    for(int i=1;i<=n;++i)
    {
        now += dis[i];
        cout<<now<<' ';
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,l,r,d;

    while(cin>>n>>m)
    {
        map<int,set<range>> t;
        set<int> ct;
        while(m--)
        {
            cin>>l>>r>>d;
            make_union(t[d],{l,r});
            cout<<"make_union["<<d<<"]: "<<print_union(t[d])<<endl;
            ct.insert(d);
        }
        memset(dis,0,sizeof(int)*(n+2));
        for(auto i : ct)
        {
            cout<<"add_range["<<i<<"]: "<<print_union(t[i])<<endl;
            for (auto j : t[i])
                add_range(j, 1);
            print_array(n);
        }
        int now = 0, max = -1, pos = 1;
        for(int i=1;i<=n;++i)
        {
            now += dis[i];
            if(now>max)
            {
                max = now;
                pos = i;
            }
        }
        cout<<pos<<endl;
    }

    return 0;
}

bool range::operator<(const range &ths) const
{
    return l<ths.l;
}