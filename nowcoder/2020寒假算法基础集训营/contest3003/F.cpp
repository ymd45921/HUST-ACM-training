/**
 * 
 */
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <cstring>

#define val first 
#define num second

using namespace std;
typedef long long longs;
typedef long double longd;
typedef pair<int,int> item;

int n;
item ali[200050],bli[200050];
bool used[200050]{0};
vector<int> H,T;
int cura,curb;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n)
    {
        memset(used,0,sizeof(used));
        H.clear(); T.clear();
        cura = curb = n;

        for(int i=1;i<=n;++i)
        {
            cin>>ali[i].val;
            ali[i].num = i;
        }
        for(int i=1;i<=n;++i)
        {
            cin>>bli[i].val;
            bli[i].num = i;
        }
        sort(ali+1,ali+1+n);
        sort(bli+1,bli+1+n);

        for(int i=1;i<=n;++i)
        {
            if(i&1)
            {
                while(used[cura])--cura;
                while(used[curb])--curb;
                if(ali[cura].val>bli[curb].val)
                {
                    used[cura] = true;
                    H.push_back(ali[cura].num);
                }
                else
                {
                    used[curb] = true;
                    H.push_back(bli[curb].num);
                } 
            }
            else
            {
                while(used[cura])--cura;
                while(used[curb])--curb;
                if(ali[cura].val>bli[curb].val)
                {
                    used[cura] = true;
                    T.push_back(ali[cura].num);
                }
                else
                {
                    used[curb] = true;
                    T.push_back(bli[curb].num);
                } 
            }
        }

        for(int i:H)
            cout<<i<<' ';
        cout<<endl;
        for(int i:T)
            cout<<i<<' ';
        cout<<endl;  
    }

    return 0;
}