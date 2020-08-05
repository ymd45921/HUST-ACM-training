#include <iostream>
#include <cstdio>

using namespace std;
typedef long long longs;

#define mylog

char s1[65],s2[65];

longs gray(int n, char* str)
{
    if(n==1) return str[0]-'0';
    if(str[0]=='1')
    {
        longs ans = (1<<n)-1;
        return ans - gray(n-1,str+1);
    }
    else
    {
        return gray(n-1,str+1);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;
#ifdef mylog
    while(1)
    {
        for(int i=0;i<n;++i)
        cin>>s1[i];
        s1[n] = s2[n] = 0;
        longs v = gray(n,s1);
        cout<<s1<<' '<<v<<endl;
    }
#endif
    for(int i=0;i<n;++i)
        cin>>s1[i];
    for(int i=0;i<n;++i)
        cin>>s2[i];
    s1[n] = s2[n] = 0;
    longs v1 = gray(n,s1);
    longs v2 = gray(n,s2);
#ifdef mylog
    cout<<s1<<' '<<v1<<endl;
    cout<<s2<<' '<<v2<<endl;
#endif
    cout<<v2-v1-1<<endl;

    return 0;
}