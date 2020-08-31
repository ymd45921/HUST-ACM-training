/**
 * 
 */
#include <iostream>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,d;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>d)
    {
        cout<<n;
        while(d--)
        cout<<"00";
        cout<<endl;
    }

    return 0;
}