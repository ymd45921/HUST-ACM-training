#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long longs;

int s[105];
char no[] = "impossible";
longs sum = 0;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, max = 0;
    sum = 0;
    while(cin>>n)
    {
        for(int i=0;i<n;++i)
        {
            cin>>s[i];
            sum += s[i];
        }
        sort(s,s+n);
        if(s[n-1] >= (sum>>1)+1)
            cout<<no<<endl;
        else
        {
            for(int i = n-1;i>=0;--i)
            cout<<s[i]<<endl;
        }
        
    }

    return 0;
}