/**
 * 
 * 为什么我现在一屑就过了
 * 
 */

#include <iostream>
#include <cstdio>

using namespace std;
typedef long long longs;

char s1[100],s2[100];

longs gray(char* s, int n)
{
    if(n==1) return s[0]-'0';
    if(s[0]=='0')
        return gray(s+1,n-1);
    else
    {
        longs ret = 1ll<<n;
        return ret-1-gray(s+1,n-1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>s1[i];
    for(int i=0;i<n;++i)
        cin>>s2[i];
    longs v1 = gray(s1,n);
    longs v2 = gray(s2,n);
    if(v1>v2) swap(v1,v2);
    longs ans = v2-v1-1;
    cout<<ans<<endl;

    return 0;
}