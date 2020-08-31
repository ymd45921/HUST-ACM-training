#include <iostream>
#include <cstring>
#include <queue>
#include <set>
#include <map>

using namespace std;
typedef long long longs;

struct msg{int tt,type;};

queue<msg> tt;
map<int,int> tab;
set<int> thistime;
int cnt = 0;

inline void process(int bound)
{
    if(tt.empty()) return;
    while(tt.size()&&tt.front().tt<=bound)
    {
        tab[tt.front().type] -= 1;
        if(!tab[tt.front().type])tab.erase(tt.front().type);
        tt.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,t,k,x;
    while(cin>>n)
    {
        cnt = 0;
        for(int i=1;i<=n;++i)
        {
            cin>>t>>k;
            int bound = t-86400;
            process(bound);
            for(int j=1;j<=k;++j)
            {
                cin>>x;
                thistime.insert(x);
            }
            for(auto xx : thistime)
            {
                tt.push({t,xx});
                tab[xx] += 1;
            }
            thistime.clear();
            cout<<tab.size()<<endl;
        }
    }

    return 0;
}