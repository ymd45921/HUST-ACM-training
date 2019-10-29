#include <iostream>
#include <cstring>

#define mst0(x) memset(x,0,sizeof(x))
#define mst1(x) memset(x,-1,sizeof(x))

using namespace std;

int n,tmp,in[105];
bool colored[105];
int ans = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    mst0(in);
    mst1(colored);
    for(int i=0;i<n;++i)
    {
        cin>>tmp;
        in[tmp]++;
        colored[tmp] = false;
    }
    int power;
    for(int i=1;i<=100;++i)
    {
        if(colored[i])continue;
        ++ans;
        for(int j=1;(power=j*i)<=100;++j)
            colored[power] = true;
    }
    cout<<ans;
    return 0;
}