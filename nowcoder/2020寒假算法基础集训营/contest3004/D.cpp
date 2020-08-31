/**
 * 
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long longs;
typedef long double longd;
typedef pair<int,int> node;

int n;
int tree[100010];
node lis[100010];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int li,lc,rc;

    while(cin>>n)
    {
        tree[0] = -1;
        int cnt = 0;
        for(int i=1;i<=n;++i)
        {
            cin>>tree[i];
            if(~tree[i])
            {
                lis[cnt] = {tree[i],i};
                ++cnt;
            }
        }
        sort(lis,lis+cnt);
        cout<<"The size of the tree is "<<cnt<<endl
            <<"Node "<<tree[1]<<" is the root node of the tree"
            <<endl;
        for(int i=0;i<cnt;++i)
        {
            li = (lis[i].second)<<1;
            lc = (li>n)?-1:tree[li];
            rc = (li^1)>n?-1:tree[li^1];

            cout<<"The father of node "<<lis[i].first<<" is "<<tree[(lis[i].second)>>1]
                <<", the left child is "<<lc<<", and the right child is "<<rc<<endl;
        }
    }

    return 0;
}