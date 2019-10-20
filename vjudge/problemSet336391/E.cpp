#include <iostream>
#include <list>

using namespace std;

int n,m;
int*in;
list<int> thelist;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n;
    in = new int[n];
    for(int i=0;i<n;++i)
    {
        cin>>in[i];
        thelist.push_back(in[i]);
    }
    cin>>m;
    thelist.remove(m);
    cout<<n<<endl<<endl;
    for(int i=0;i<n;++i)cout<<in[i]<<' ';
    cout<<endl<<endl<<thelist.size()<<endl<<endl;
    for(auto i=thelist.begin();i!=thelist.end();++i)
        cout<<*i<<' ';
    return 0;
}