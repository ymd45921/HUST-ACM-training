#include <iostream>
#include <list>

using namespace std;
typedef long long longs;

longs n,m;
longs*in;
list<longs> thelist;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n)
    {
        in = new longs[n];
        for(int i=0;i<n;++i)
        {
            cin>>in[i];
            thelist.push_back(in[i]);
        }
        cin>>m;
        thelist.remove(m);
        cout<<n<<endl;
        for(int i=0;i<n-1;++i)cout<<in[i]<<' ';
        cout<<in[n-1]<<endl<<thelist.size()<<endl;
        auto i=thelist.begin();
        auto lim = --thelist.end();
        for(;i!=lim;++i)
            cout<<*i<<' ';
        cout<<*lim<<endl;
        delete[] in;
        thelist.clear();
    }
    return 0;
}