/**
 * 
 */
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
typedef long long longs;
typedef long double longd;

int n,m;
string s1,s2;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while(cin>>n>>m)
    {
        int x = min(n,m);
        int cnt = 0;
        cin>>s1>>s2;

        for(int i=0;i<x;++i)
        {
            if(s1[i]-s2[i])++cnt;
        }
        cnt+=max(n,m)-x;

        cout<<cnt<<endl;
    }

    return 0;
}