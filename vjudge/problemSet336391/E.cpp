#include <iostream>

using namespace std;
typedef long long longs;

longs n,m;
longs*in;
longs length;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    in = new longs[n];
    for(int i=0;i<n;++i)
    {
        cin>>in[i];
    }
    cin>>m;
    length = n;

    for(int i=0;i<n;++i)
    {
        if(in[i]==m)--length;
    }
    cout<<n<<endl;
    for(int i=0;i<n;++i)cout<<in[i]<<' ';
    cout<<endl<<length<<endl;
    for(int i=0;i<n;++i)
    {
        if(in[i]==m);
        else cout<<in[i]<<' ';
    }
    return 0;
}