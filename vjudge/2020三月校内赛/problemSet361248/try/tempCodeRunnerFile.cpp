/**
 * 
 * 
 * 可以暴力
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;
typedef long long longs;

pair<int,int> s[40];

inline void init()
{
    for(int i=0;i<=30;++i)
        s[i].second = i;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,sum;

    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>s[i].first,sum+=s[i].first;
    sort(s+1,s+1+n);
    if(s[n].first>=sum>>1)
        cout<<"impossible";
    else
    {
        for(int i=n;i>0;--i)
            cout<<s[n].second<<' ';
        cout<<endl;
    }

    return 0;
}