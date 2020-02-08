/**
 * 
 * T……T了？这难道不是单纯的模拟吗
 * 
 * woc 卡memset 这辈子第一次见
 */
#include <iostream>
#include <cstring>

using namespace std;
typedef int longs;
typedef long double longd;

const char AC[] = "Accepted";
const char UB[] = "Undefined Behaviour";
const char RE[] = "Runtime error";

int t,n,m,p;
int x,y,val;
enum flag{Running, Accepted, Undefined, Error} flag;
const longs lb = 0;
longs ub,ptr;
int mem[20000010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>t;
    while(t--)
    {
        cin>>n>>m>>p;
        ub = n*m;
        flag = Running;
        memset(mem,0,sizeof(int)*ub);

        while(p--)
        {
            cin>>x>>y>>val;
            if(flag==Error) continue;
            ptr = (longs)x*m + (longs)y;
            if(ptr<lb||ptr>=ub)
            {
                flag = Error;
                continue;
            }
            else if(x<0||x>=n||y<0||y>=m) flag = Undefined;
            mem[ptr] = val;
        }

        if(flag == Error) cout<<RE<<endl;
        else
        {
            ptr = 0;
            for(int i=0;i<n;++i)
            {
                for(int j=0;j<m;++j)
                {
                    cout<<mem[ptr]<<' ';
                    ++ptr;
                }
                cout<<endl;
            }
            if(flag == Undefined) cout<<UB<<endl;
            else cout<<AC<<endl;
        }
    }

    return 0;
}