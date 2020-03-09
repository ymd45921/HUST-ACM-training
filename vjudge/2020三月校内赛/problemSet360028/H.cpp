/**
 * 
 * WA: -6
 * Helped
 * 
 */
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;
typedef long long longs;

const int aweek = 10080;
const char cannot[] = "no such mower";
const int INF = 0x7fffffff;

struct lmer
{
    string name;
    int price,crate,time,recharge;
    longs unitwork,unittime;

    lmer(){}
    explicit lmer(string &s);
    void print();
    bool operator<(const lmer& that) const;
    bool canDo(int s);
};

int l,m;
lmer li[105];
int p,c,t,r;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>l>>m)
    {
        for(int i=1;i<=m;++i)
        {
            string in;
            while(!in.length())getline(cin,in);
            li[i] = lmer(in);
//            li[i].print();
//            cout<<endl;
        }
        int lowestprice = INF,pos = 0;
        sort(li+1,li+1+m);
        for(int i=1;i<=m;++i)
            if(li[i].canDo(l))
            {
                lowestprice = li[i].price;
                pos = i;
                cout<<li[i].name<<endl;
                break;
            }
        if(pos) for(int i=pos+1;i<=m;++i)
            {
                if(li[i].price==lowestprice)    //漏了逻辑
                    if(li[i].canDo(l)) cout<<li[i].name<<endl;
                    else continue;
                else break;
            }
        else cout<<cannot<<endl;
    }

    return 0;
}

lmer::lmer(string &s)
{
    stringstream ss;
    auto pos1 = s.find(',');
//    assert(s[pos1]==',');
    name = s.substr(0,pos1);
    s = s.substr(pos1);
    ss.str(s);
    char ch;
    ss>>ch>>price>>ch>>crate>>ch>>time>>ch>>recharge;
    unitwork = (longs)crate*time;
    unittime = (longs)time + recharge;
}

void lmer::print()
{
    cout<<"name: "<<name<<endl
        <<"price: "<<price<<endl
        <<"rate: "<<crate<<endl
        <<"time: "<<time<<endl
        <<"recharge: "<<recharge
        <<endl;
}

bool lmer::operator<(const lmer &that) const
{
    return price<that.price;
}

bool lmer::canDo(int s)
{
    double foruse = aweek;
    double times = foruse/(double)unittime;     //help：要用double
    return times * unitwork >= s;
}
