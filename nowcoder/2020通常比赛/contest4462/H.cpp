#include <iostream>
#include <map>
#include <vector>

using namespace std;
typedef long long longs;
typedef long double longd;

const int N = 1e5+10;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,l,r,d;

    while(cin>>n>>m)
    {
        vector<int> mount[N];
        vector<int> umount[N];
        map<int,int> mounted;
        while(m--)
        {
            cin>>l>>r>>d;
            mount[l].push_back(d);
            umount[r].push_back(d);
        }
        int now = 0, max = -1, pos = 1;
        for(int i=1;i<=n;++i)
        {
            for(int j : mount[i])
            {
                if(!mounted[j])++now;
                ++mounted[j];
            }
            if(now>max)
            {
                max = now;
                pos = i;
            }
            for(int j : umount[i])
            {
                --mounted[j];
                if(!mounted[j])--now;
            }
        }
        cout<<pos<<endl;
    }

    return 0;
}