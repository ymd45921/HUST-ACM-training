/**
 * 
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;
typedef long long longs;
typedef long double longd;

const string wtnl = "wtnl";
const string no = "No";
const string yes = "Yes";

longs a,b,c;
longd x,y,z;

bool check()
{
    longs max = a>b?a:b;
    max = max>c?max:c;
    if(a+b+c-max<=max)return false;
    else return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout<<fixed<<setprecision(2);

    while(cin>>a>>b>>c)
    {
        if(!check())
        {
            cout<<wtnl<<endl;
            continue;
        }
        y = (a-b+c)/2.0l;
        x = (a+b-c)/2.0l;
        z = (c+b-a)/2.0l;
        longd ans[3] = {x,y,z};
        sort(ans,ans+3);
        cout<<yes<<endl;
        cout<<ans[0]<<' '<<ans[1]<<' '<<ans[2]<<endl;
    }

    return 0;
}